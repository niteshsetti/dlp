#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Servo.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const char* ssid = "Manaswinisetti";
const char* password = "Manju@5e6";
LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4;
const byte COLS = 4;
int servo_pin = 10;
Servo myservo;
int angle = 0;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {D2, D3, D4, D5};
byte colPins[COLS] = {D6, D7, D8, D9};
int c = 0;
String cc = "";
String empid = "";
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
void setup() {
  Wire.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }
  while (!Serial);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME TO");
  lcd.setCursor(0, 1);
  lcd.print(" AA Technologies");
  delay(2000);
  dis();
  myservo.attach(servo_pin);
}
void dis()
{
  lcd.clear();
  lcd.print("Enter EMPID");
}

void mains()
{
  char customKey = customKeypad.getKey();
  if (customKey) {
    c = c + 1;
    if (customKey)
    {
      cc = cc + String(customKey);
      lcd.setCursor(c, 1);
      lcd.print("*");
      Serial.println(cc);
      if (cc.length() == 6 && empid == "")
      {
        if (WiFi.status() == WL_CONNECTED) {

          HTTPClient http;

          http.begin("http://knvsrestuarant.000webhostapp.com/lock.php?Item=" + cc);
          int httpCode = http.GET();

          if (httpCode > 0)
          {

            String payload = http.getString();
            Serial.println(payload);
            if (payload == "1")
            {
              empid = cc;
              cc = "";
              c = 0;
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Enter Passcode");
              Serial.println("Enter Passcode");
            }
            else
            {
              Serial.println("Invalid EMPID");
              cc = "";
              c = 0;
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Invalid EMPID");
              setup();
            }

          }

          http.end();   //Close connection

        }
      }
    }
    if (cc.length() == 6 && empid != "")
    {
      HTTPClient http;
      http.begin("http://knvsrestuarant.000webhostapp.com/getlock.php?Items=" + empid);
      int httpCodes = http.GET();

      if (httpCodes > 0)
      {

        String payloads = http.getString();
        Serial.println(payloads);
        if (payloads == cc)
        {
          cc = "";
          c = 0;
          empid="";
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Door opened");
          delay(1000);
          setup();
        }
        else {
          cc = "";
          c = 0;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Invalid Passcode");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Try Again !!!");
          delay(1000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter Passcode");
          Serial.println("Enter Passcode");


        }
      }
    }
  }
}
void loop() {
  mains();

}
