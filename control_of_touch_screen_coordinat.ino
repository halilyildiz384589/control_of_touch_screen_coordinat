#include <Adafruit_ST7789.h>   //.kbv for ENES
#include <Fonts/FreeSans9pt7b.h>   //.kbv use FreeFonts etc
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

#define Arial_24 &FreeSans9pt7b    //.kbv FreeFonts use address
#define Arial_48 &FreeSans12pt7b
#define Arial_60 &FreeSans18pt7b
#define ILI9341_BLACK  0x0000      //.kbv stupid hard-coded colors 
#define ILI9341_RED    0xF800
#define ILI9341_GREEN  0x07E0
#define ILI9341_YELLOW 0xFFE0
#define CS_PIN  4  //Waveshare Touch
#define TFT_DC  7  //Waveshare 
#define TFT_CS 10  //Waveshare
#define TFT_BL  9  //Waveshare backlight
// MOSI=11, MISO=12, SCK=13
#define TIRQ_PIN  2


XPT2046_Touchscreen ts(CS_PIN);
Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_BL);


void setup() {
  Serial.begin(9600);
  //tft.begin();  //.kbv diff method used for ST7789
  tft.init(240, 320, SPI_MODE0); //.kbv for ENES
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  ts.begin();
  ts.setRotation(1);
  while (!Serial && (millis() <= 1000));
}

boolean wastouched = true;

void loop() {
  boolean istouched = ts.touched();
  if (istouched) {
    TS_Point p = ts.getPoint();
    if (!wastouched) {
      tft.fillScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_YELLOW);
      tft.setFont(Arial_60);
      tft.setCursor(60, 80);
      tft.print("Touch");
    }
    //tft.fillRect(100, 150, 140, 60, ILI9341_BLACK); //.kbv
    tft.fillRect(100, 130, 140, 60, ILI9341_BLACK); //.kbv FreeFont topline
    tft.setTextColor(ILI9341_GREEN);
    tft.setFont(Arial_24);
    tft.setCursor(100, 150);
    tft.print("X = ");
    tft.print(p.x);
    tft.setCursor(100, 180);
    tft.print("Y = ");
    tft.print(p.y);
    Serial.print(", x = ");
    Serial.print(p.x);
    Serial.print(", y = ");
    Serial.println(p.y);
  } else {
    if (wastouched) {
      tft.fillScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_RED);
      tft.setFont(Arial_48);
      tft.setCursor(120, 50);
      tft.print("No");
      tft.setCursor(80, 120);
      tft.print("Touch");
    }
    Serial.println("no touch");
  }
  wastouched = istouched;
  delay(100);
}

