void PrintStartupMessage(){
  tft.setCursor(1,0);
  tft.setTextColor(MAGENTA);tft.setTextSize(3);tft.println("TFT_test.ino");
  tft.setTextColor(BLUE);   tft.setTextSize(1);tft.println("Resolution 320x240 px\nCapable of 500 pixels/sec");
  tft.setTextColor(BLUE);   tft.setTextSize(1);tft.println("Zachary Lauritzen 2022");
  tft.setTextColor(GREEN);  tft.setTextSize(2);tft.print("Beginning program...");
}

void DisplayConfigScreen(){
  DrawButton(0,0,3,1,BLUE,"Option 0",2,CYAN, 0,0);
  DrawButton(0,1,3,1,BLUE,"Option 1",2,CYAN, 0,1);
  DrawButton(0,2,3,1,BLUE,"Option 2",2,CYAN, 0,2);
  DrawButton(0,3,3,1,BLUE,"Option 3",2,CYAN, 0,3);
  DrawButton(4,0,3,1,BLUE,"Option 4",2,CYAN, 0,4);
  DrawButton(4,1,3,1,BLUE,"Option 5",2,CYAN, 0,5);
  DrawButton(4,2,3,1,BLUE,"Option 6",2,CYAN, 0,6);
  DrawButton(4,3,3,1,BLUE,"Option 7",2,CYAN, 0,7);
  DrawButton(0,5,3,1,GREEN,"  SAVE"   ,2,GREEN,0,10);
  DrawButton(5,5,3,1,YELLOW,"  EXIT"  ,2,YELLOW,0,11);  
  
  DrawStatusLight(3,0,bitRead(message_buffer,0));
  DrawStatusLight(3,1,bitRead(message_buffer,1));
  DrawStatusLight(3,2,bitRead(message_buffer,2));
  DrawStatusLight(3,3,bitRead(message_buffer,3));
  DrawStatusLight(7,0,bitRead(message_buffer,4));
  DrawStatusLight(7,1,bitRead(message_buffer,5));
  DrawStatusLight(7,2,bitRead(message_buffer,6));
  DrawStatusLight(7,3,bitRead(message_buffer,7));

}


void DisplayMainScreen(){
  tft.setCursor(6,0);
  tft.setTextColor(10);
  tft.setTextSize(2);
  tft.setTextColor(WHITE,BLACK);
  tft.print("Radio transmitter active!!");
  delay(500);
  tft.setCursor(6,0);
  tft.print("                          ");
  tft.drawCircle(compass_center[0], compass_center[1], compass_radius , GREEN);
  DrawButton(6,5,2,1,BLACK,"Menu",2,BLUE,0,11);
  DrawButton(0,5,2,1,RED,"STOP",2,RED,1,222);
  //DrawTile  (0,0,1,6,RED,"",3,RED,0);
}


void UpdateCompass(){
  //DrawTile(0,0,8,1,WHITE,"MAIN DISPLAY",3,MAGENTA ,0);
  angle = byte(millis()/50)/255.0 * 360.0;

  if(true){
    tft.drawCircle(compass_center[0] +sin(north_old)       *(compass_radius - 10) , compass_center[1]  -cos(north_old)        *(compass_radius - 10),8,BLACK);
    tft.drawCircle(compass_center[0] +sin(north_angle)     *(compass_radius - 10) , compass_center[1]  -cos(north_angle)      *(compass_radius - 10),8,GREEN);
    tft.drawCircle(compass_center[0] +sin(steering_old)    *(compass_radius + 10) , compass_center[1]  -cos(steering_old)     *(compass_radius + 10),8,BLACK);
    tft.drawCircle(compass_center[0] +sin(steering_angle)  *(compass_radius + 10) , compass_center[1]  -cos(steering_angle)   *(compass_radius + 10),8,MAGENTA);
    
    north_old     = north_angle;
    steering_old  = steering_angle;
    
  }
  
}

void DisplayEmergencyScreen(){
  tft.fillScreen(RED);
  tft.setCursor(55,90);
  tft.setTextSize(4);
  tft.setTextColor(BLACK);
  tft.println("EMERGENCY\n     STOP!");
  
  while (1){
    delay(1000);
    }
}
