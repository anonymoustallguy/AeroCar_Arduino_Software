void SetupGyro(){
  uint8_t sys_cal   = 0;
  uint8_t gyro_cal  = 0;
  uint8_t accel_cal = 0;
  uint8_t mag_cal   = 0;

  if(!bno.begin()){
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    }
  
  delay(100);
  bno.setExtCrystalUse(true);
  /*
  Serial.print("WAITING FOR GYRO CALIBRATION");
  while(gyro_cal <2 or mag_cal <2){
    delay(200);
    bno.getCalibration(&sys_cal ,&gyro_cal , &accel_cal, &mag_cal);
    //Serial.print(".");
    Serial.print(gyro_cal);Serial.print("  ");Serial.println(mag_cal);
  }
  Serial.println("CALIBRATION COMPLETE");
  */
}
