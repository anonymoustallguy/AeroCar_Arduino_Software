void getTouchPoint(){
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // scale from 0->1023 to tft.width
    //Serial.print(p.x);Serial.print('\t');Serial.print(p.y);
    p.x = map(p.x, TS_MINX, TS_MAXX, 240, 0);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);
    touchPixel[0] = p.x;
    touchPixel[1] = p.y;
    //Serial.print("\ttouchGrid: ");Serial.print(touchGrid[0]);Serial.print(',');Serial.println(touchGrid[1]);
    touchGrid[0] = round((p.y)/gridSize); //flip x and y
    touchGrid[1] = round((p.x)/gridSize);

    ConfigScreenTouch(gridButtonLinks[touchGrid[0]][touchGrid[1]]);
    
    //tft.drawRect(touchGrid[0]*gridSize+5, touchGrid[1]*gridSize+5, gridSize-10, gridSize-10, MAGENTA);
    //DrawTile(touchGrid[0],touchGrid[1],1,1,BLUE,String(gridButtonLinks[touchGrid[0]][touchGrid[1]]),1,WHITE,0);
    //delay(250);
    //DisplayConfigScreen();

//    digitalWrite(13, HIGH);
//    TSPoint p = ts.getPoint();  //NOT NECESSARY
//    
//    while (p.z > MINPRESSURE && p.z < MAXPRESSURE){
//      TSPoint p = ts.getPoint();
//    }
//    digitalWrite(13, LOW);
//    pinMode(XM, OUTPUT);
//    pinMode(YP, OUTPUT);

    delay(100);
  }
  
  
}


void ConfigScreenTouch(byte buttonID){
  if (buttonID <8){
    bitWrite(message_buffer,buttonID,!bitRead(message_buffer,buttonID)); 
    DisplayConfigScreen();
  }
  else if (buttonID == 10){
    delay(100);
    byte garbage = 69;
    SoftSerial.write(garbage);
    delay(100);
//    message = message_buffer;

    for (int n=0;n<8;n++){
//      Serial.print(bitRead(message,n));Serial.print(',');
    }
//    Serial.println();
    
    tft.setCursor(10,gridSize*4.3);
    tft.setTextSize(2);
    tft.setTextColor(GREEN,BLACK);
    tft.print("CONFIG SAVED!"); 
    delay(500);  
    tft.setCursor(10,gridSize*4.3);
    tft.print("             ");

    
    }
    else if (buttonID == 11){
      screen = !screen;
    }
    else if (buttonID == 222){
      DisplayEmergencyScreen();
    }

    
  }
