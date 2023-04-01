void SendWatchdog(){
  SoftSerial.write(byte(255));
}

void Abort(){
  //set abort GPIO pin to trigger chute relay and other nano (other nano should ground out motor PWM signal to force it off (use 1K resistor on this nano and bare gpio on RADIO nano)
  //set panic flag to stop all other processes
  //motor off
  //if not tumbling, servo to middle
    //else detach servo
  
}
