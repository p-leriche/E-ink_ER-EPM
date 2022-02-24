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
//  epd.DisplayFrame();
  /**
    * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
    * In this case, a smaller image buffer is allocated and you have to 
    * update a partial display several times.
    * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
    */

Serial.println("e-Ink Demo");
  unsigned char image[1024];
  Paint paint(image, 152, 18);    //width should be the multiple of 8
  
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(22, 2, "e-ink Demo", &Font16, COLORED);
  epd.SetPartialWindowBlack(paint.GetImage(), 0, 3, paint.GetWidth(), paint.GetHeight());

  paint.Clear(COLORED);
  paint.DrawStringAt(20, 4, "(White on color)", &Font12, UNCOLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 0, 24, paint.GetWidth(), paint.GetHeight());

  paint.SetWidth(40);
  paint.SetHeight(36);

//TOP ROW:
// Rectange
  paint.Clear(UNCOLORED);
  paint.DrawRectangle(5, 3, 35, 33, COLORED);
  paint.DrawLine(5, 3, 35, 33, COLORED);
  paint.DrawLine(35, 3, 5, 33, COLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 32, 42, paint.GetWidth(), paint.GetHeight());

// Shaded Rectange
  paint.Clear(UNCOLORED);
  paint.DrawShadedRectangle(5, 3, 35, 33);
  epd.SetPartialWindowBlack(paint.GetImage(), 72, 42, paint.GetWidth(), paint.GetHeight());

// Filled Rectangle
  paint.Clear(UNCOLORED);
  paint.DrawFilledRectangle(5, 3, 35, 33, COLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 112, 42, paint.GetWidth(), paint.GetHeight());

//SECOND ROW:
// Circle
  paint.Clear(UNCOLORED);
  paint.DrawCircle(20, 18, 15, COLORED);
  epd.SetPartialWindowBlack(paint.GetImage(), 32, 78, paint.GetWidth(), paint.GetHeight());

// Shaded Circle
  paint.Clear(UNCOLORED);
  paint.DrawShadedCircle(20, 18, 15);
  epd.SetPartialWindowRed(paint.GetImage(), 72, 78, paint.GetWidth(), paint.GetHeight());

//Filled circle
  paint.Clear(UNCOLORED);
  paint.DrawFilledCircle(20, 18, 15, COLORED);
  epd.SetPartialWindowBlack(paint.GetImage(), 112, 78, paint.GetWidth(), paint.GetHeight());

//THIRD ROW
// Circle
  paint.Clear(COLORED);
  paint.DrawCircle(20, 18, 15, UNCOLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 32, 114, paint.GetWidth(), paint.GetHeight());

// Shaded Circle
  paint.Clear(COLORED);
  paint.DrawShadedCircle(20, 18, 15);
  epd.SetPartialWindowBlack(paint.GetImage(), 72, 114, paint.GetWidth(), paint.GetHeight());

//Filled circle
  paint.Clear(COLORED);
  paint.DrawFilledCircle(20, 18, 15, UNCOLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 112, 114, paint.GetWidth(), paint.GetHeight());

  paint.SetWidth(32);
  paint.SetHeight(110);
  paint.SetRotate(ROTATE_270);
  paint.Clear(COLORED);
  paint.DrawStringAt(8, 8, "Sideways!", &Font16, UNCOLORED);
  epd.SetPartialWindowBlack(paint.GetImage(), 0, 42, paint.GetWidth(), paint.GetHeight());
  
  epd.DisplayFrame();


     delay(15000);
//    epd.ClearFrame();
    
    epd.Sleep();

}
