///___SoftwareSerial setup and variables///
#include <SoftwareSerial.h>
#include <Servo.h>
const byte rxPin = 5;
const byte txPin = 6;
SoftwareSerial SoftSerial (rxPin, txPin);

///___Gyro/Mag setup and variables___///
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
Adafruit_BNO055 bno = Adafruit_BNO055(55);
double gravityVector[3];
double magVector[3];

///___Control/process variables___///
byte NANO_steering;
byte NANO_throttle;
byte NANO_code;
bool NANO_code_bit[8];
bool PANIC = false;

///___Set up timing variables___///
unsigned long t_SoftSerial;
unsigned long t_gyro;
unsigned long t_mag;

///___SERIAL COMMUNICATION VARIABLES___///
unsigned long t_SoftSerial_available;
bool SoftSerial_flag = false;

///___Functions___///
void GetSoftSerial();
void SetupGyro();
void GetGyro();
void Abort();
void GetMag();
void SendToDevices();


///___TESTING STUFF___///
Servo steeringServo;
const unsigned int servo_val = 1500;
            //////////////////
            //  VOID SETUP  //
            //////////////////
void setup() {
///___Begin Serial Communication___///
Serial.begin(115200);
SoftSerial.begin(9600);
SetupGyro();
Serial.println("ready");

///___TESTING STUFF___///
steeringServo.attach(13);
steeringServo.writeMicroseconds(1500);
}


            /////////////////
            //  VOID LOOP  //
            /////////////////
void loop() {

if (SoftSerial.available() && SoftSerial_flag == false){      //if there is a message in the software serial buffer (and the flag hasn't been flipped yet)...
  SoftSerial_flag = true;             //set the message recieved flag to true
  t_SoftSerial_available = millis();  //start message reception timer
}

if (SoftSerial_flag && millis()-t_SoftSerial_available > 5){  //if it has been 5ms since the software serial message was received, it's time to read it
  if (SoftSerial.read()==255){                                //make sure the message starts from the beginning (with a 255 byte)
    steeringServo.writeMicroseconds(map(SoftSerial.read(),0,255,1000,2000));
    while(SoftSerial.available()){                            //TESTING** print the data to the serial monitor***
      Serial.print(SoftSerial.read());Serial.print("\t");
    }
    Serial.println();
  }
  while (SoftSerial.available()){       //clear out the software serial buffer
    SoftSerial.read();
  }
  SoftSerial_flag = false;              //reset the data available flag
}


//if(SoftSerial.available()>3 and not PANIC){
//  delay(10);
//  GetSoftSerial();  
//}
//if(abs(millis()-t_gyro) > 99 and not PANIC){
//  GetGyro();
//}
//if(abs(millis()-t_mag) > 99 and not PANIC){
//  GetMag();  
//}
//
//
//if((millis()-t_SoftSerial)>250){ //panic if comms to other nano are lost
//  PANIC = true;
//  while(1){
//    Serial.println("SOFTWARE SERIAL TO RADIO NANO LOST!");
//    delay(1000);
//    
//  }
//}
delay(1);
//Serial.println(millis()-t_SoftSerial);
}
