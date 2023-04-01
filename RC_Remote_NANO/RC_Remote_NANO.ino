#include <SoftwareSerial.h>
#include <RH_RF69.h>
#include <SPI.h>

///___INITIALIZE OBJECTS___///



///___SOFTWARE SERIAL VARIABLES___///
byte message_out[4];
byte message_in;
SoftwareSerial SoftSerial = SoftwareSerial(6,7,0);

///___JOYSTICK VARIABLES___///
unsigned int joy_cal[4];
const int x1 = A1;
const int y1 = A2;
const int x2 = A6;
const int y2 = A7;

///___RADIO VARIABLES___//
#define RF69_FREQ 915.0
#define RFM69_INT     3  // 
#define RFM69_CS      4  // 4 for UNO, 53 for Mega 2560
#define RFM69_RST     5  // "A"
RH_RF69 rf69(RFM69_CS, RFM69_INT);
byte radiopacket[3];


///___DEFINE FUNCTIONS___///
void InitializeRadio();


void setup() {
///___START SERIAL COMM.___///
SoftSerial.begin(9600);
Serial.begin(115200);Serial.println("Serial communication online");

///___CALIBRATE JOYSTICKS AND INITIALIZE SOFTWARE SERIAL BUFFER___///
message_out[0]=255;
  //delay(10);
  //joy_cal[0] = analogRead(x1);
  //delay(10);
  //joy_cal[1] = analogRead(y1);
  //delay(10);
  //joy_cal[2] = analogRead(x2);
  //delay(10);
  //joy_cal[3] = analogRead(y2);
  //delay(10);


///___INITIALIZE RADIO___///
  InitializeRadio();
  delay(1000);  //delay to read serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:

///___BUILD AND SEND SOFTWARE SERIAL MESSAGE___///
message_out[1]=map(analogRead(x1),0,1023,0,254);   //for now, just output mapped joystick values
message_out[2]=map(analogRead(y1),0,1023,0,254);
message_out[3]=map(analogRead(x2),0,1023,0,254);

for(int n=0;n<4;n++){
  SoftSerial.write(message_out[n]);
  Serial.print(message_out[n]);Serial.print("\t");
}
Serial.println();

///___ASSEMBLE AND SEND RADIO PACKET
radiopacket[0] = message_out[1];
radiopacket[1] = message_out[2];
radiopacket[2] = message_out[3];

rf69.send((uint8_t *)radiopacket, 3); //send a message
rf69.waitPacketSent();

//uint8_t buf[RH_RF69_MAX_MESSAGE_LEN]; //check for reply
//uint8_t len = sizeof(buf);




///___GET INPUT FROM SOFTWARE SERIAL___///
if (SoftSerial.available()){
  delay(5);                             //wait for message to complete
  if (SoftSerial.peek() != 0){          //check for garbage (0) message
    message_in = SoftSerial.read(); //if it's good, record the incoming message
    for (int n=0;n<8;n++){
      Serial.print(bitRead(message_in  ,n));Serial.print("-"); //output bits to serial monitor
    }                                                                 //...
    Serial.println();                                                 //...
    delay(5000);                                                      //wait 5 sec to read the bits in the serial monitor manually
  }
    while(SoftSerial.available()){    //clear the software serial buffer
      SoftSerial.read();
    }
}

delay(50);
}
