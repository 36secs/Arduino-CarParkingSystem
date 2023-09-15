#include <Servo.h> // Include the servo library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // Initialize the LCD with the correct I2C address and column/row numbers

Servo myservo;

#define ir_enter 2
#define ir_back 4

#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8
#define ir_car5 9
#define ir_car6 10

int S1 = 0, S2 = 0, S3 = 0, S4 = 0, S5 = 0, S6 = 0;
int flag1 = 0, flag2 = 0;
int slot = 6;

void setup() {
  Serial.begin(9600);

  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);
  pinMode(ir_car5, INPUT);
  pinMode(ir_car6, INPUT);

  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);

  myservo.attach(3);
  myservo.write(90);

  lcd.begin(20, 4);
  lcd.setCursor(0, 1);
  lcd.print("    Car Parking  ");
  lcd.setCursor(0, 2);
  lcd.print("       System     ");
  delay(2000);
  lcd.clear();

  Read_Sensor();

  int total = S1 + S2 + S3 + S4 + S5 + S6;
  slot = slot - total;
}

void loop() {
  Read_Sensor();

  lcd.setCursor(0, 0);
  lcd.print("   Available Slots: ");
  lcd.print(slot);
  lcd.print("    ");

  lcd.setCursor(0, 1);
  lcd.print(S1 ? "S1: Fill " : "S1: Empty");

  lcd.setCursor(10, 1);
  lcd.print(S2 ? "S2: Fill " : "S2: Empty");

  lcd.setCursor(0, 2);
  lcd.print(S3 ? "S3: Fill " : "S3: Empty");

  lcd.setCursor(10, 2);
  lcd.print(S4 ? "S4: Fill " : "S4: Empty");

  lcd.setCursor(0, 3);
  lcd.print(S5 ? "S5: Fill " : "S5: Empty");

  lcd.setCursor(10, 3);
  lcd.print(S6 ? "S6: Fill " : "S6: Empty");

  if (digitalRead(ir_enter) == LOW && flag1 == 0) {
    if (slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo.write(180);
        slot--;
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print(" Sorry, Parking Full ");
      delay(1500);
    }
  }

  if (digitalRead(ir_back) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo.write(180);
      slot++;
    }
  }

  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo.write(90);
    flag1 = 0;
    flag2 = 0;
  }

  delay(1);
}

void Read_Sensor() {
  S1 = digitalRead(ir_car1) == LOW ? 1 : 0;
  S2 = digitalRead(ir_car2) == LOW ? 1 : 0;
  S3 = digitalRead(ir_car3) == LOW ? 1 : 0;
  S4 = digitalRead(ir_car4) == LOW ? 1 : 0;
  S5 = digitalRead(ir_car5) == LOW ? 1 : 0;
  S6 = digitalRead(ir_car6) == LOW ? 1 : 0;
}
