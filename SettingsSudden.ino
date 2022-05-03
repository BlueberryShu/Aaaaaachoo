//#include <Adafruit_BMP085.h>
//#include <Adafruit_MPU6050.h>
//#include <Adafruit_Sensor.h>
//#include <Wire.h>
//#include <SPI.h>
//#include <SD.h>

#define RedDiode 5 //пин красного диода
#define YellowDiode 7 //пин жёлтого диода
#define BlueDiode 9 //пин синего диода
#define RedBut 6 //кнопка при красном диоде, ПЕРЕПАЯТЬ!!!
#define YellowBut 8 //кнопка при жёлтом диоде
#define BlueBut 10 //кнопка при синем диоде
#define Detach 3 //пин концевика
#define Buzpin 2 //пин буззера
#define CSpin 14 //пин кардридэра
#define MotPin1 16 //1и3 пины мотора
#define MotPin2 17 //2и4 пины мотора
#define DetectV A1 //пин детектора напряжения(цепрчка резисторов)

//Adafruit_BMP085 bmp;
//Adafruit_MPU6050 mpu;

float V;
 
void setup() {
  pinMode(RedDiode,OUTPUT); 
  pinMode(YellowDiode,OUTPUT);
  pinMode(BlueDiode,OUTPUT);
  pinMode(RedBut,INPUT_PULLUP);
  pinMode(YellowBut,INPUT_PULLUP);
  pinMode(BlueBut,INPUT_PULLUP);
  pinMode(Detach,INPUT_PULLUP);
  pinMode(Buzpin,OUTPUT);
  pinMode(MotPin1,OUTPUT);
  pinMode(MotPin2,OUTPUT);
}

//  V = analogRead(DetectV) / 67.42;

//  if (V < 8.2) {
//     digitalWrite(RedDiode,1);
//     while (1);
//  }
//
//  if (!bmp.begin()) {
//    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
//    while (1) {
//      digitalWrite(RedDiode,1);
//      delay(1000);
//      digitalWrite(RedDiode,0);
//      delay(1000);
//    }
//  }

//  if (!mpu.begin()) {
//    Serial.println("Failed to find MPU6050 chip");
//    digitalWrite(YellowDiode,1); 
//    while (1){
//    }
//  }
//
//  if (!SD.begin(CSpin)) {
//    Serial.println("Card failed, or not present");
//    while (1) {
//      digitalWrite(YellowDiode,1);
//      delay(1000);
//      digitalWrite(YellowDiode,0);
//      delay(1000);;
//    }
//  }
//
//  digitalWrite(BlueDiode,1);
//  Serial.begin (9600);
//}




void loop() {
  //Serial.println (digitalRead(YellowBut));
  //Serial.println (analogRead(DetectV)/67.42);
  analogWrite (Buzpin, 50);
  delay (2000);
  analogWrite (Buzpin, 0);

}
