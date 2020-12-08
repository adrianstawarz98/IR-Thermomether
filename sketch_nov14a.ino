#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h> 
 
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27, 16, 2);
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
const int dioda = 8;
const int buzzer = 9;
// SDA - A4 SCL - A5
void setup()
{
 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(dioda, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  mlx.begin();  
  lcd.clear();
  lcd.setCursor(1 ,0);
  lcd.print("IR Temperature");
  lcd.setCursor(5,1);
  lcd.print("Sensor :)");
  delay(4000);
}
 
void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  if(distance > 5){
    digitalWrite(dioda, LOW);
    lcd.clear();
    lcd.setCursor(0 ,0);
    lcd.print("Jestes za daleko");
    lcd.setCursor(3,1);
    lcd.print("Zbliz sie");
    delay(500);
  }
  else{
  digitalWrite(dioda, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp:  ");
  lcd.print(mlx.readObjectTempC());
  lcd.print(" C");  
  lcd.setCursor(0,1);
  lcd.print("Distance:");
  lcd.println(distance);
  Serial.print("Distance:");
  Serial.print(distance);
  Serial.println("cm");
  lcd.println("cm");
  Serial.println();
  if(mlx.readObjectTempC() > 30.5){
    lcd.setCursor(0,0);
    lcd.print("Temp:f   ");
    lcd.print(mlx.readObjectTempC());
    lcd.print(" C");
    lcd.setCursor(0,1);
    lcd.print("Distance:");
    lcd.println(distance);
    tone(buzzer, 500);
    delay(100);
    noTone(buzzer);
  }
  delay(500);
  }
  
}
