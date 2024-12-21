#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

// ตั้งค่าจอ LCD (ปรับที่อยู่ I2C หากจำเป็น)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ตั้งค่าขาของเซ็นเซอร์และ Buzzer
const int sensorPin = 2;  // ขาเซ็นเซอร์ 
const int buzzerPin = 3;   // ขา Buzzer

// ตัวแปรนับจำนวน
int counter = 7;

void setup() {
  // เริ่มต้นจอ LCD
  lcd.init();
  lcd.backlight();

  // กำหนดโหมดของขา I/O
  pinMode(sensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // เริ่มต้นการแสดงผล
  lcd.setCursor(0, 0);
  lcd.print("Object Counter");
  updateDisplay();

}

void loop() {
  // อ่านค่าจากเซ็นเซอร์
  int sensorValue = digitalRead(sensorPin);

  if (sensorValue == LOW) {      // ตรวจจับวัตถุได้เมื่อค่าเป็น LOW
    tone(buzzerPin, 1000, 200);  // ส่งเสียง 1kHz เป็นเวลา 200ms

    // ลดตัวนับ
    counter--;

    // หากตัวนับถึง 0 ให้รีเซ็ตเป็น 7
    if (counter < 0) {
      counter = 7;
    }

    // อัปเดตการแสดงผล
    updateDisplay();

    // รอจนกว่าวัตถุจะพ้นเซ็นเซอร์
    while (digitalRead(sensorPin) == LOW) {
      delay(10);
    }
  }
}
void updateDisplay() {
  lcd.setCursor(0, 1);
  lcd.print("Count: ");
  lcd.print(counter);
  lcd.print(" ");  // เคลียร์ช่องเกิน
}
