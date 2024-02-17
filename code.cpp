
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial espSerial(4, 5);  // RX, TX

int buzzer = 6;
int motor = 8;

int eye_blink_sensor = 7;

int eye_blink_sense = 0;

int eye_blink_count = 0;
int sleep_detection = 0;

int data = 0;

void setup() {
  Serial.begin(9600);  // Initialize serial
  espSerial.begin(9600);

  lcd.init();
  lcd.clear();
  lcd.backlight();
  pinMode(eye_blink_sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motor, OUTPUT);

  digitalWrite(motor, LOW);
}

void loop() {
  if (digitalRead(eye_blink_sensor) == 1 && eye_blink_sense == 0) {
    eye_blink_sense = 1;
    eye_blink_count = 0;
  }

  else if (digitalRead(eye_blink_sensor) == 0 && eye_blink_sense == 1) {
    eye_blink_sense = 0;
  }

  eye_blink_count++;
  delay(100);

  lcd.setCursor(0, 0);
  lcd.print("   DROWSINESS   ");

  if (eye_blink_count > 50) {
    lcd.setCursor(0, 1);
    lcd.print("    DETECTED    ");
    digitalWrite(buzzer, HIGH);
    digitalWrite(motor, LOW);
    Serial.println("DETECTED");
    data = 1;
  } else {
    lcd.setCursor(0, 1);
    lcd.print("  NOT DETECTED  ");
    digitalWrite(buzzer, LOW);
    digitalWrite(motor, HIGH);
    Serial.println("NOT DETECTED");
    data = 0;
  }
  espSerial.println(data);
  delay(100);
}
35_driver_drowsiness_detection.txt
Displaying driver_drowsiness_ppt team 12.pptx.