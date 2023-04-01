void DrawButton(unsigned int grid_x, unsigned int grid_y, unsigned int grid_w, unsigned int grid_h, uint16_t buttonColor, String text, byte text_size, uint16_t textColor, bool singleChar, byte buttonID){
  byte button_margin = 2;
  
  byte text_margin = gridSize/2-text_size*4 + 1;
  byte center_offset = 10;
  if (singleChar == true){
     center_offset = 21-3*text_size;
  }
  
  tft.drawRect(gridSize*grid_x + button_margin, gridSize*grid_y + button_margin, gridSize*grid_w - 2*button_margin, gridSize*grid_h - 2*button_margin, buttonColor);
  tft.setCursor(gridSize*grid_x + center_offset, gridSize*grid_y + text_margin);
  tft.setTextSize(text_size);
  tft.setTextColor(textColor);
  tft.print(text);
  for (int a=grid_x;a<grid_w+grid_x;a++){
    for (int b=grid_y;b<grid_h+grid_y;b++){
      gridButtonLinks[a][b] = buttonID;
    }
  }
  
//  gridButtonLinks[grid_x][grid_y] = buttonID;

  
}

void DrawTile(unsigned int grid_x, unsigned int grid_y, unsigned int grid_w, unsigned int grid_h, uint16_t buttonColor, String text, byte text_size, uint16_t textColor, bool singleChar){
  byte button_margin = 2;
  
  byte text_margin = gridSize/2-text_size*4 + 1;
  byte center_offset = 10;
  if (singleChar == true){
     center_offset = 21-3*text_size;
  }
  
  tft.fillRect(gridSize*grid_x + button_margin, gridSize*grid_y + button_margin, gridSize*grid_w - 2*button_margin, gridSize*grid_h - 2*button_margin, buttonColor);
  tft.setCursor(gridSize*grid_x + center_offset, gridSize*grid_y + text_margin);
  tft.setTextSize(text_size);
  tft.setTextColor(textColor);
  tft.print(text);  
}


void DrawStatusLight(unsigned int grid_x, unsigned int grid_y, bool input_bit){
  byte center_offset;
  byte text_margin = gridSize/2-1*4 + 1;
  tft.setTextSize(1);

  tft.fillCircle(gridSize*grid_x + gridSize/2, gridSize*grid_y + gridSize/2, gridSize/2-6, BLACK);
  
  
  if (input_bit){
    center_offset = 14;
    
    tft.fillCircle(gridSize*grid_x + gridSize/2, gridSize*grid_y + gridSize/2, gridSize/2-6, GREEN);
    tft.setCursor(gridSize*grid_x + center_offset, gridSize*grid_y + text_margin);
    tft.setTextColor(BLACK);
    tft.print("ON");  
  }
  else {
    center_offset = 12;
    tft.drawCircle(gridSize*grid_x + gridSize/2, gridSize*grid_y + gridSize/2, gridSize/2-6, RED);
    tft.setCursor(gridSize*grid_x + center_offset, gridSize*grid_y + text_margin);
    tft.setTextColor(RED);
    tft.print("OFF");  
  }

}
