void GetSoftSerial(){
  if(SoftSerial.peek() == 255){         //the message should start with a byte reading 255
    SoftSerial.read();                  //clear 255 from software serial buffer
    
    if(SoftSerial.peek() != 255){       //if the steering byte is good, read it
      NANO_steering     = SoftSerial.read();
      
      if(SoftSerial.peek() != 255){     //if the throttle byte is good, read it
        NANO_throttle   = SoftSerial.read();
        
        if(SoftSerial.peek() != 255){   //if the code byte is good, read it
          NANO_code     = SoftSerial.read();
          t_SoftSerial = millis();            //update time of last good message if all bytes were valid, this will make garbled data time-out
        }
      }
    }


    /////////// TESTING OUTPUT ////////////
    for (int n=0;n<8;n++){
      NANO_code_bit[n]  = bitRead( NANO_code , n);
//      Serial.print(NANO_code_bit[n]);
//      if (n<7){
//        Serial.print(',');
//      }
    }
//    Serial.print("\tSt: ");Serial.print(NANO_steering);
//    Serial.print("\tTh: ");Serial.print(NANO_throttle);
//    Serial.print("\tCo: ");Serial.println(NANO_code);
  ///////////// END TESTING OUTPUT ///////////
  }
  else {  //What to do if message fails
//    Serial.print("MESSAGE FAILED");Serial.println(SoftSerial.peek());   //TESTING ONLY
  }
  
  while(SoftSerial.available()){
    SoftSerial.read();                  //clear any remaining data from the serial buffer
  }
}

void GetGyro(){
  //sensors_event_t event; ///MIGHT BE ABLE TO INCLUDE IN SETUP OR INITIALIZATION??
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  gravityVector[0] = euler[0];
  gravityVector[1] = euler[1];
  gravityVector[2] = euler[2]; 
  t_gyro = millis();
//  Serial.print('|');
//  Serial.print(gravityVector[0]);Serial.print(',');
//  Serial.print(gravityVector[1]);Serial.print(',');
//  Serial.print(gravityVector[2]);
}

void GetMag(){
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
  magVector[0] = euler[0];
  magVector[1] = euler[1];
  magVector[2] = euler[2];
  t_mag = millis();
//  Serial.print('|');
//  Serial.print(magVector[0]);Serial.print(',');
//  Serial.print(magVector[1]);Serial.print(',');
//  Serial.print(magVector[2]);Serial.println();
}
