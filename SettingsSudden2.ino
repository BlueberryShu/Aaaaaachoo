#include <Adafruit_BMP085.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

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

Adafruit_BMP085 bmp;
Adafruit_MPU6050 mpu;

float V, Alt, StartAlt, A, maxalt;
unsigned long T;
bool StP, Ap, DetP, LP;
byte stage = 0;


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

  V = analogRead(DetectV) / 67.42;

  
  if (V < 8.2) {
     digitalWrite(RedDiode,1);
     while (1);
  }
  if (V > 8.3) {
     digitalWrite(BlueDiode,1);
  }
  if (8.2 < V && V < 8.3) {
     digitalWrite(YellowDiode,1);
  }

  if (!bmp.begin()) {
    
    while (1) {
      tone(Buzpin, 2048, 200);
      delay(400);
      tone(Buzpin, 2048, 200);
      delay(1000);
    }
    
  }

  if (!mpu.begin()) {
    //Serial.println("Failed to find MPU6050 chip");
    
      
    while (1){
      tone(Buzpin, 2048, 200);
      delay(400);
      tone(Buzpin, 2048, 200);
      delay(400);
      tone(Buzpin, 2048, 200);
      delay(1000); 
    }
  }

  /*if (!SD.begin(CSpin)) {
    //Serial.println("Card failed, or not present");
    while (1) {
      tone(Buzpin, 2048, 200);
      delay(400);
      tone(Buzpin, 2048, 200);
      delay(400);
      tone(Buzpin, 2048, 200);
      delay(400);
      tone(Buzpin, 2048, 200);
      delay(1000); 
    }
  }*/
  while(digitalRead(BlueBut) == 1) {
      if (digitalRead(YellowBut) == 0) {
        digitalWrite(MotPin1, 1);
        digitalWrite(MotPin2, 0);
      }
      else if (digitalRead(RedBut) == 0) {
        digitalWrite(MotPin1, 0);
        digitalWrite(MotPin2, 1);
      }
      else {
        digitalWrite(MotPin1, 0);
        digitalWrite(MotPin2, 0);
      }
  }
  maxalt = bmp.readAltitude();
  tone(Buzpin, 2048, 200);
  Serial.begin (9600);
  StartAlt = bmp.readAltitude();

}




void loop() {
  Alt = bmp.readAltitude() - StartAlt;
  T = millis();
  V = analogRead(DetectV) / 67.42;
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  A = sqrt(sq(a.acceleration.x) + sq(a.acceleration.y) + sq(a.acceleration.z));
  String dataString = (String)T + "|" + Alt + "|" + A + "|" + V + "|" + StP + "|" + Ap + "|" + DetP + "|" + LP;
  Serial.println(dataString);
  
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }



  switch (stage) {
    case 0:
      if (Alt >= 3.0) {
        StP = 1;
        stage = 1;
      }
      break;
    case 1:
      if (Alt >= maxalt) {
        maxalt = Alt;
      }
      else if (Alt < maxalt - 2.0) {
        Ap = 1;
        stage = 2;
      }
      break;
    case 2:
          if(digitalRead(Detach) == 0) {
             digitalWrite(MotPin1, 1);
             digitalWrite(MotPin2, 0);
          }
          else {
            digitalWrite(MotPin1, 0);
            digitalWrite(MotPin2, 0);
            DetP = 1;
            stage = 3;
          }
          break;
    case 3:
      if (Alt <= 10.0) {
        LP = 1;
        stage = 4;
      }
      break;
    case 4:
      //tone(Buzpin, 2048, 100);
      break;
    default:
      break;
    
  }
  
}
