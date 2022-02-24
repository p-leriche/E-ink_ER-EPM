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
#include "imagedata.h"
#include "epdpaint.h"

#define COLORED     0
#define UNCOLORED   1


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    Epd epd;
    if (epd.Init() != 0) {
        Serial.print("e-Ink init failed");
        return;
    }

  /* This clears the SRAM of the e-ink display */
  epd.ClearFrame();
//  epd.DisplayFrame();
  /**
    * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
    * In this case, a smaller image buffer is allocated and you have to 
    * update a partial display several times.
    * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
    */
  unsigned char image[1024];
  Paint paint(image, 152, 18);    //width should be the multiple of 8 

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(8, 2, "e-Ink Demo", &Font16, COLORED);
  epd.SetPartialWindowBlack(paint.GetImage(), 0, 3, paint.GetWidth(), paint.GetHeight());

  paint.Clear(COLORED);
  paint.DrawStringAt(8, 2, "www.buydisplay.com", &Font12, UNCOLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 0, 24, paint.GetWidth(), paint.GetHeight());
  
  paint.SetWidth(64);
  paint.SetHeight(64);

  paint.Clear(UNCOLORED);
  paint.DrawRectangle(0, 0, 40, 50, COLORED);
  paint.DrawLine(0, 0, 40, 50, COLORED);
  paint.DrawLine(40, 0, 0, 50, COLORED);
  epd.SetPartialWindowBlack(paint.GetImage(), 8, 45, paint.GetWidth(), paint.GetHeight());
  
  paint.Clear(UNCOLORED);
  paint.DrawCircle(16, 16, 15, COLORED);
  epd.SetPartialWindowBlack(paint.GetImage(), 64, 45, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawFilledRectangle(0, 0, 40, 50, COLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 8, 100, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawFilledCircle(16, 16, 15, COLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 64, 100, paint.GetWidth(), paint.GetHeight());

  /* This displays the data from the SRAM in e-Ink module */
  epd.DisplayFrame();
   
     delay(2000); 
  
    epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);
          delay(2000);     
    epd.DisplayFrame(IMAGE_BLACK1, IMAGE_RED1);
          delay(2000);     

     delay(15000);
    epd.ClearFrame();
    epd.DisplayFrame();
    
    epd.Sleep();
}

void loop() {
  // put your main code here, to run repeatedly:

}
