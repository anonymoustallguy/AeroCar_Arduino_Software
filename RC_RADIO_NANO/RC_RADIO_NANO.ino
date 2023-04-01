#define RF69_FREQ 915.0
#include <RH_RF69.h>

#include <SoftwareSerial.h>
const byte rxPin = 5;
const byte txPin = 6;
SoftwareSerial SoftSerial (rxPin, txPin);

///___RADIO VARIABLES, FUNCTIONS, AND DEFINITIONS___///
#define RFM69_INT     2  // 
#define RFM69_CS      10  //
#define RFM69_RST     9  // "A"
#define RF69_FREQ 915.0
RH_RF69 rf69(RFM69_CS, RFM69_INT); // Singleton instance of the radio driver
void InitializeRadio();

///___COMMUNICATION VARIABLES___///
byte RADIO_steering = 0;
byte RADIO_throttle = 0;
byte RADIO_code     = 0;
byte data[3];
byte message[4];

bool RADIO_code_bit[8];

void setup() 
{
  ///___SERIAL SETUP___///
  Serial.begin(115200);
  SoftSerial.begin(9600);
  Serial.println("RFM69_RC_Receive_Test");
  Serial.println();
  ///___VARIABLE SETUP___///
  message[0] = byte(255);
  
  ///___RADIO SETUP___///
  InitializeRadio();
  rf69.setTxPower(20);  // range from 14-20 for power, 2nd arg must be true for 69HCW
  char key[16] = "sampleencryptify";
  rf69.setEncryptionKey(key);
  rf69.setModemConfig(RH_RF69::GFSK_Rb4_8Fd9_6);//---> Set modulation type and bitrate.
  
/*  _______EXAMPLE BITRATE CONFIGURATIONS_______                      ___TRANS TIME (4 BYTES W/REPLY)___
 *   
 *FSK_Rb2Fd5 = 0,    ///< FSK, Whitening, Rb = 2kbs,    Fd = 5kHz     <--111 MS TRANS TIME
  FSK_Rb2_4Fd4_8,    ///< FSK, Whitening, Rb = 2.4kbs,  Fd = 4.8kHz   <-- 95 MS
  FSK_Rb4_8Fd9_6,    ///< FSK, Whitening, Rb = 4.8kbs,  Fd = 9.6kHz   <-- 53 MS
  FSK_Rb9_6Fd19_2,   ///< FSK, Whitening, Rb = 9.6kbs,  Fd = 19.2kHz  <-- 32 MS
  FSK_Rb19_2Fd38_4,  ///< FSK, Whitening, Rb = 19.2kbs, Fd = 38.4kHz
  FSK_Rb38_4Fd76_8,  ///< FSK, Whitening, Rb = 38.4kbs, Fd = 76.8kHz
  FSK_Rb57_6Fd120,   ///< FSK, Whitening, Rb = 57.6kbs, Fd = 120kHz
  FSK_Rb125Fd125,    ///< FSK, Whitening, Rb = 125kbs,  Fd = 125kHz
  FSK_Rb250Fd250,    ///< FSK, Whitening, Rb = 250kbs,  Fd = 250kHz
  FSK_Rb55555Fd50,   ///< FSK, Whitening, Rb = 55555kbs,Fd = 50kHz for RFM69 lib compatibility

  GFSK_Rb2Fd5,        ///< GFSK, Whitening, Rb = 2kbs,    Fd = 5kHz     <--111 MS TRANS TIME
  GFSK_Rb2_4Fd4_8,    ///< GFSK, Whitening, Rb = 2.4kbs,  Fd = 4.8kHz   <-- 95 MS ** same as previous
  GFSK_Rb4_8Fd9_6,    ///< GFSK, Whitening, Rb = 4.8kbs,  Fd = 9.6kHz   <-- 53 MS ** better RSSI
  GFSK_Rb9_6Fd19_2,   ///< GFSK, Whitening, Rb = 9.6kbs,  Fd = 19.2kHz  <-- 33 MS * very good RSSI
  GFSK_Rb19_2Fd38_4,  ///< GFSK, Whitening, Rb = 19.2kbs, Fd = 38.4kHz
  GFSK_Rb38_4Fd76_8,  ///< GFSK, Whitening, Rb = 38.4kbs, Fd = 76.8kHz
  GFSK_Rb57_6Fd120,   ///< GFSK, Whitening, Rb = 57.6kbs, Fd = 120kHz
  GFSK_Rb125Fd125,    ///< GFSK, Whitening, Rb = 125kbs,  Fd = 125kHz
  GFSK_Rb250Fd250,    ///< GFSK, Whitening, Rb = 250kbs,  Fd = 250kHz
  GFSK_Rb55555Fd50,   ///< GFSK, Whitening, Rb = 55555kbs,Fd = 50kHz

  OOK_Rb1Bw1,         ///< OOK, Whitening, Rb = 1kbs,    Rx Bandwidth = 1kHz.     <--220 MS TRANS TIME
  OOK_Rb1_2Bw75,      ///< OOK, Whitening, Rb = 1.2kbs,  Rx Bandwidth = 75kHz.    <--180 MS
  OOK_Rb2_4Bw4_8,     ///< OOK, Whitening, Rb = 2.4kbs,  Rx Bandwidth = 4.8kHz.   <-- 95 MS
  OOK_Rb4_8Bw9_6,     ///< OOK, Whitening, Rb = 4.8kbs,  Rx Bandwidth = 9.6kHz.   <-- 50 MS
  OOK_Rb9_6Bw19_2,    ///< OOK, Whitening, Rb = 9.6kbs,  Rx Bandwidth = 19.2kHz.  <-- 32 MS
  OOK_Rb19_2Bw38_4,   ///< OOK, Whitening, Rb = 19.2kbs, Rx Bandwidth = 38.4kHz. 
  OOK_Rb32Bw64,       ///< OOK, Whitening, Rb = 32kbs,   Rx Bandwidth = 64kHz. 
 */
}

void loop() {
 if (rf69.available()) {
    // Should be a message for us now   
    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf69.recv(buf, &len)) {
      if (!len) return;

        RADIO_steering = buf[0];
        RADIO_throttle = buf[1];
        RADIO_code     = buf[2];

        Serial.print("Steer: ");Serial.print(RADIO_steering);Serial.print("\tThrottle: ");Serial.print(RADIO_throttle);Serial.print("\t");
        
        message[1]=buf[0];
        message[2]=buf[1];
        message[3]=buf[2];
        SoftSerial.write(message , 4);
        for (int n=0;n<8;n++){
          RADIO_code_bit[n]  = bitRead( RADIO_code , n);
          Serial.print(RADIO_code_bit[n]);Serial.print(",");
        }
        Serial.println();
    }
    
  }
  
}
