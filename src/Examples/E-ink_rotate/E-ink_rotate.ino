/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-EPM0154-1R
Display is Hardward SPI 4-Wire SPI Interface 
Tested and worked with:
Works with Arduino 1.6.0 IDE  
Works with Arduino DUE,Arduino mega2560,Arduino UNO Board
****************************************************/

#include <SPI.h>
#include "ER-ERM.h"
#include "epdpaint.h"

#define COLORED     0
#define UNCOLORED   1

    Epd epd;

char line[80];
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    if (epd.Init() != 0) {
        Serial.print("e-Ink init failed");
        return;
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  /* This clears the SRAM of the e-ink display */
  epd.ClearFrame();

  /**
    * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
    * In this case, a smaller image buffer is allocated and you have to 
    * update a partial display several times.
    * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
    */

Serial.println("Rotate Demo");
  unsigned char image[1024];
  Paint paint(image, 152, 14);    //width should be the multiple of 8
  
  paint.Clear(COLORED);
  paint.DrawStringAt(44, 2, "Rotate Demo", &Font12, UNCOLORED);
  epd.SetPartialWindowBlack(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());


  paint.SetWidth(56);
  paint.SetHeight(24);

  paint.Clear(COLORED);
  paint.DrawStringAt(8, 7, "0deg", &Font12, UNCOLORED);
//  paint.DrawRectangle(0, 0, 49, 19, COLORED);
//  paint.DrawFilledCircle(0, 0, 3, COLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 88, 72, paint.GetWidth(), paint.GetHeight());
  sprintf(line, "At %d %d: %dx%d\n", 88, 72, paint.GetWidth(), paint.GetHeight());
  Serial.print(line);

  paint.SetRotate(ROTATE_180);
  paint.Clear(COLORED);
  paint.DrawStringAt(8, 7, "180deg", &Font12, UNCOLORED);
//  paint.DrawRectangle(0, 0, 49, 19, COLORED);
//  paint.DrawFilledCircle(0, 0, 3, COLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 8, 72, paint.GetWidth(), paint.GetHeight());
  sprintf(line, "At %d %d: %dx%d\n\n", 8, 72, paint.GetWidth(), paint.GetHeight());
  Serial.print(line);
  
  paint.SetWidth(24);
  paint.SetHeight(56);

  paint.SetRotate(ROTATE_90);
  paint.Clear(COLORED);
  paint.DrawStringAt(8, 7, "90deg", &Font12, UNCOLORED);
//  paint.DrawRectangle(0, 0, 49, 19, COLORED);
//  paint.DrawFilledCircle(0, 0, 3, COLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 64, 96, paint.GetWidth(), paint.GetHeight());
  
  paint.SetRotate(ROTATE_270);
  paint.Clear(COLORED);
  paint.DrawStringAt(8, 7, "270deg", &Font12, UNCOLORED);
//  paint.DrawRectangle(0, 0, 49, 19, COLORED);
//  paint.DrawFilledCircle(0, 0, 3, COLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 64, 16, paint.GetWidth(), paint.GetHeight());

  epd.DisplayFrame();


     delay(15000);
//    epd.ClearFrame();
    
    epd.Sleep();

}
