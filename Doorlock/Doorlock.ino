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
String arr[100];
String pass[100];
String kk = "";
String kk1 = "";
String cc = "";
int y = 0;
int yy = 0;
int count = 0;
int key = 0;
String empid = "";
int passenter = 0;
String emp = "";
String passcode = "";
int n = 0;
int c = 0;
int pos;
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
void setup() {
  Wire.begin();
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.println("Connecting..");

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
  mains();
  myservo.attach(D10);

}
void dis()
{
  lcd.clear();
  lcd.print("Enter EMPID");
}
void mains()
{

  if (WiFi.status() == WL_CONNECTED)
  {

    HTTPClient http, httpp, httpcount;

    http.begin("http://duvp.000webhostapp.com/Doorlockproject/lock.php");
    int httpCode = http.GET();
    httpp.begin("http://duvp.000webhostapp.com/Doorlockproject/getlock.php");
    int httpCode1 = httpp.GET();
    httpcount.begin("http://duvp.000webhostapp.com/Doorlockproject/count.php");
    int httpCode2 = httpcount.GET();
    if (httpCode > 0 && httpCode1 > 0)
    {

      String payload = http.getString();
      String payload1 = httpp.getString();
      String payload2 = httpcount.getString();
      n = payload2.toInt();
      for (int i = 0; i < payload.length(); i++)
      {
        if (payload[i] == ',')
        {
          arr[y] = kk;
          kk = "";
          y++;
        }
        else
        {
          kk = kk + payload[i];
        }
      }
      for (int j = 0; j < payload1.length(); j++)
      {
        if (payload1[j] == ',')
        {
          pass[yy] = kk1;
          kk1 = "";
          yy++;
        }
        else
        {
          kk1 = kk1 + payload1[j];
        }
      }
    }

    http.end();   //Close connection

  }
  Serial.println("The Records are:");
  for (int i = 0; i < n; i++)
  {
    Serial.println(arr[i]);
  }
  Serial.println("-----------------------------");
  Serial.println("The Passwords are:");
  for (int k = 0; k < n; k++)
  {
    Serial.println(pass[k]);
  }
  Serial.println();
}
void loop() {
  char customKey = customKeypad.getKey();
  if (customKey)
  {
    c = c + 1;
    cc = cc + String(customKey);
    lcd.setCursor(c, 1);
    lcd.print("*");
    Serial.println(cc);
    if (cc.length() == 6 && empid == "")
    {
      for (int i = 0; i < n; i++)
      {
        if (arr[i] == cc)
        {
          count = 1;
          empid = cc;
          cc = "";
          key = i;
          c = 0;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter Passcode");
          Serial.println("Enter Your Passcode");
          passcode = pass[key];
          emp = arr[key];
          Serial.println(emp);
          Serial.println(passcode);
          break;
        }
      }
    }


    if (cc.length() == 6 && empid != "")
    {
      if (emp == empid && passcode == cc)
      {
        Serial.println("Door Open");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Door opened");
        HTTPClient http;
        http.begin("http://duvp.000webhostapp.com/Doorlockproject/log.php");
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        String cool = empid;
        String data = "&name=" + cool;
        int httpCode = http.POST(data);
        if (httpCode > 0) {
          String response = http.getString();
          Serial.println(httpCode);
          Serial.println(response);
        }
        else {
          Serial.print("Error on sending post");
          Serial.println(httpCode);
        }
        for (pos = 270; pos >= 0; pos -= 2) { // goes from 0 degrees to 180 degrees
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(12);                       // waits 15ms for the servo to reach the position
        }
        for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(12);                       // waits 15ms for the servo to reach the position
        }
        setup();
        count = 0;
        empid = "";
        cc = "";
        c = 0;
      }
      else {
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
        Serial.println("Invalid Passcode");
        cc = "";
      }
    }
    if (count == 0 && cc.length() == 6)
    {
      Serial.println("Invalid Empid");
      c = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Invalid EMPID");
      setup();
      cc = "";
    }
  }
}
