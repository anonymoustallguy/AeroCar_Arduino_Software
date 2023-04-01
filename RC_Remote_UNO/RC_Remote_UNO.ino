#include <Adafruit_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <string.h>
#include <SoftwareSerial.h>


///___LCD CONFIGURATION___///
// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin


///___TOUCH CONFIGURATION___///
#define YP A3       // must be an analog pin, use "An" notation!
#define XM A2       // must be an analog pin, use "An" notation!
#define YM 9        // can be a digital pin
#define XP 8        // can be a digital pin

#define TS_MINX 950 //CALIBRATION DATA (PORTRAIT MODE)
#define TS_MINY 62    
#define TS_MAXX 100   
#define TS_MAXY 925
#define MINPRESSURE 10
#define MAXPRESSURE 1000
unsigned int touchPixel[2];

///___COLOR SETUP___///
// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define GRAY    0x4044
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


///___INITIALIZE TFT DISPLAY & TOUCH___///
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


///___INITIALIZE FUNCTIONS___///
void LCD_INIT();
void PrintStartupMessage();
void DisplayConfigScreen();
void DrawButton (unsigned int grid_x, unsigned int grid_y, unsigned int grid_w, unsigned int grid_h, uint16_t buttonColor, String text, byte text_size, uint16_t textColor, bool singleChar, byte buttonID);
void DrawTile   (unsigned int grid_x, unsigned int grid_y, unsigned int grid_w, unsigned int grid_h, uint16_t buttonColor, String text, byte text_size, uint16_t textColor, bool singleChar);
void getTouchPoint();
void ConfigScreenTouch(byte buttonID);
void DisplayEmergencyScreen();
void DisplayMainScreen();

///___BUTTON FUNCTIONS AND VARIABALES___///
int   touchGrid [2];
const int  gridSize = 40;
//typedef void (*FuncArray)(bool);
//FuncArray ScreenFunctions[8][8];
int gridButtonLinks[8][8];
byte message_buffer;
//byte message;

///___MISC. VARIABLES___///
double angle;
double angle_old;
unsigned int compass_center[2] = {320/2 , 240/2};
unsigned int compass_radius=80;
unsigned int indicator_radius=40;
bool screen = 0;
double north_angle;
double steering_angle;
double north_old;
double steering_old;

///___COMMUNICATION SETUP___///
SoftwareSerial SoftSerial = SoftwareSerial(10, 11, false);
byte serial_out_buffer = 0;


void setup() {
  Serial.begin(115200);
  memset(gridButtonLinks,255,sizeof(gridButtonLinks));
  SoftSerial.begin(9600);
  LCD_INIT();
  PrintStartupMessage();
  delay(500);
}

void loop() {
  memset(gridButtonLinks,255,sizeof(gridButtonLinks));
  tft.fillScreen(BLACK);

  if (screen ==1){
    DisplayMainScreen();
  }
  while (screen == 1){  //MAIN SCREEN
    if(SoftSerial.available()>2){
      if(SoftSerial.read() == 255){
        north_angle = SoftSerial.read() * 6.2832/254.0;
        steering_angle = SoftSerial.read() * 6.2832/254.0;
        Serial.print(north_angle);Serial.print("\t");Serial.println(steering_angle);  //print output for testing
      }
      while(SoftSerial.available()){
        SoftSerial.read();
      }
    }
    UpdateCompass();
    getTouchPoint();
    delay(5);
  }

  
  memset(gridButtonLinks,255,sizeof(gridButtonLinks));
  tft.fillScreen(BLACK);
  
  if (screen == 0){
//    message_buffer = message;
    delay(10);
    DisplayConfigScreen();
  }
  while (screen == 0){  //CONFIG SCREEN
    getTouchPoint();
    delay(5);
  }
  SoftSerial.write(message_buffer);
  
}
