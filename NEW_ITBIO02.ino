#define Motot_P1 5
#define Motot_N1 4
#define Motot_P2 3
#define Motot_N2 2
#include <ultrasonic.h>
ULTRASONIC U1;
#include"dht11.h"
#include"heart.h"
const int sensorPin = A4;
int sensorValue = 0;
DHT dht;
#include <SoftwareSerial.h>
SoftwareSerial ss(A3, A4);
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); char rx_data, rx_data1, py_rx_data, helth;
int count = 0, count1 = 0, F, temp;
bool py_flag = true;
int r;
int count6;
int avg;
void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  U1.begin(A0, A1);
  pinMode(Motot_P1, OUTPUT);
  pinMode(Motot_N1, OUTPUT);
  pinMode(Motot_P2, OUTPUT);
  pinMode(Motot_N2, OUTPUT);
  pinMode(sensorPin, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("EYE WHEEL CHAIR");
  delay(2000);
}
void loop() {
  //  sensorValue = digitalRead(sensorPin);
  //
  //
  //  Serial.print("Sensor Value: ");
  //  Serial.print(sensorValue);

  heart();
  lcd.clear();
  dht.dht_read(6);
  temp = (dht.temperature * 9) / 5 + 32;
  //Serial.println(temp);
  F = U1.ultra();
  // Serial.println(F);
  lcd.setCursor(0, 0);
  lcd.print("U:" + String(F) + " T:" + String(temp) + " H:" + String(G_i));
  firebase("*" + String(temp) + "#" + "^" + String(G_i) + "#");

  py_data();
  if ((F < 25 && F > 1 && F != 0)) { //stop
    F = U1.ultra();
    digitalWrite(Motot_P1, LOW);
    digitalWrite(Motot_N1, LOW);
    digitalWrite(Motot_P2, LOW);
    digitalWrite(Motot_N2, LOW);
    delay(500);
    B_MOOD();
    delay(1000);
    S_MOOD();
  }



  //  lcd.setCursor(0, 1);
  //  lcd.print("WAITING FOR DATA");
  //  delay(400);
  //  while (ss.available() > 0) {
  //    helth = ss.read();
  //
  //      lcd.clear();
  //      lcd.setCursor(3, 0);
  //      lcd.print("py data RX");
  //      Resp();
  //      ss.println("*" + String(G_i) + "#," + String(temp) + "," #$");
  //      delay(1000);
  //    }
  //  }
}
void py_data() {
  while (Serial.available() > 0) {
    py_rx_data = Serial.read();
    Serial.println(py_rx_data);
    while (py_rx_data == 'A' && py_flag == true) {
      Serial.println("enter");
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("START");
      delay(200);
      while (Serial.available() > 0) {
        rx_data = Serial.read();
        Serial.println(rx_data);
        switch (rx_data) {
          case 'F':
            F_MOOD();
            //py_flag = false;
            break;
          case 'B':
            B_MOOD();
            //flag = false;
            break;
          case 'R':
            // flag = false;
            R_MOOD();
            break;
          case 'L':
            // flag = false;
            L_MOOD();
            break;
          case 'A':
            lcd.setCursor(0, 0);
            lcd.print("STOP");
            py_flag = false;
            break;
        }
      }
    }
    while (py_rx_data == 'A' && py_flag == false) {
      S_MOOD();
      Serial.println("stop");
      py_flag = true;
      break;
    }
  }
}

void F_MOOD() {
  F = U1.ultra();
  // Serial.println(F);
  lcd.setCursor(0, 0);
  lcd.print("U:" + String(F) + " T:" + String(temp) + " H:" + String(G_i));
  py_data();
  if ((F < 25 && F > 1 && F != 0)) { //stop
    F = U1.ultra();
    digitalWrite(Motot_P1, LOW);
    digitalWrite(Motot_N1, LOW);
    digitalWrite(Motot_P2, LOW);
    digitalWrite(Motot_N2, LOW);
    delay(500);
    B_MOOD();
    delay(1000);
    S_MOOD();
  }
  digitalWrite(Motot_P1, LOW);
  digitalWrite(Motot_N1, HIGH);
  digitalWrite(Motot_P2, LOW);
  digitalWrite(Motot_N2, HIGH);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("FORWARD");  delay(1000);

}
void B_MOOD() {
  F = U1.ultra();
  // Serial.println(F);
  lcd.setCursor(0, 0);
  lcd.print("U:" + String(F) + " T:" + String(temp) + " H:" + String(G_i));
  py_data();
  if ((F < 25 && F > 1 && F != 0)) { //stop
    F = U1.ultra();
    digitalWrite(Motot_P1, LOW);
    digitalWrite(Motot_N1, LOW);
    digitalWrite(Motot_P2, LOW);
    digitalWrite(Motot_N2, LOW);
    delay(500);
    B_MOOD();
    delay(1000);
    S_MOOD();
  }
  digitalWrite(Motot_P1, HIGH);
  digitalWrite(Motot_N1, LOW);
  digitalWrite(Motot_P2, HIGH);
  digitalWrite(Motot_N2, LOW);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("BACKWARD");
  delay(1000);
}
void R_MOOD() {
  F = U1.ultra();
  // Serial.println(F);
  lcd.setCursor(0, 0);
  lcd.print("U:" + String(F) + " T:" + String(temp) + " H:" + String(G_i));
  py_data();
  if ((F < 25 && F > 1 && F != 0)) { //stop
    F = U1.ultra();
    digitalWrite(Motot_P1, LOW);
    digitalWrite(Motot_N1, LOW);
    digitalWrite(Motot_P2, LOW);
    digitalWrite(Motot_N2, LOW);
    delay(500);
    B_MOOD();
    delay(1000);
    S_MOOD();
  }
  digitalWrite(Motot_P1, HIGH);
  digitalWrite(Motot_N1, LOW);
  digitalWrite(Motot_P2, LOW);
  digitalWrite(Motot_N2, HIGH);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("RIGHT");
  delay(1000);
}
void L_MOOD() {
  F = U1.ultra();
  // Serial.println(F);
  lcd.setCursor(0, 0);
  lcd.print("U:" + String(F) + " T:" + String(temp) + " H:" + String(G_i));
  py_data();
  if ((F < 25 && F > 1 && F != 0)) { //stop
    F = U1.ultra();
    digitalWrite(Motot_P1, LOW);
    digitalWrite(Motot_N1, LOW);
    digitalWrite(Motot_P2, LOW);
    digitalWrite(Motot_N2, LOW);
    delay(500);
    B_MOOD();
    delay(1000);
    S_MOOD();
  }
  digitalWrite(Motot_P1, LOW);
  digitalWrite(Motot_N1, HIGH);
  digitalWrite(Motot_P2, HIGH);
  digitalWrite(Motot_N2, LOW);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("LEFT");
  delay(1000);
}
void S_MOOD() {
  digitalWrite(Motot_P1, LOW);
  digitalWrite(Motot_N1, LOW);
  digitalWrite(Motot_P2, LOW);
  digitalWrite(Motot_N2, LOW);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("STOP");
  delay(1000);
}

void Resp(void)
{
  for (int i = 0; i < 20; i++)
  {
    lcd.clear();
    lcd.setCursor(12, 0);
    lcd.print(i);
    r = digitalRead(sensorPin);
    // Serial.println(r);
    if (r == 0)
    {
      count6++;
      lcd.setCursor(12, 1);
      lcd.print(count6);
      // Serial.println(count6);
    }
    delay(1000);
  }
  avg = (count6 * 3);
  lcd.setCursor(0, 1);
  lcd.print(avg);
  //  Serial.println("RESP:");
  //  Serial.print(avg);
  count6 = 0;
  delay(1000);
}
void firebase(String s)
{
  for (int i = 0; i <= s.length(); i++)
  {
    Serial.write(s[i]);
  }
  delay(2000);
}
