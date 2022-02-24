/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/

#ifndef EPDPAINT_H
#define EPDPAINT_H

// Display orientation
#define ROTATE_0            0
#define ROTATE_90           1
#define ROTATE_180          2
#define ROTATE_270          3

// Color inverse. 1 or 0 = set or reset a bit if set a colored pixel
#define IF_INVERT_COLOR     1

#include "fonts.h"

class Paint {
public:
    Paint(unsigned char* image, int width, int height);
    ~Paint();
    void Clear(int colored);
    int  GetWidth(void);
    void SetWidth(int width);
    int  GetHeight(void);
    void SetHeight(int height);
    int  GetRotate(void);
    void SetRotate(int rotate);
    unsigned char* GetImage(void);
    void DrawAbsolutePixel(int x, int y, int colored);
    void DrawPixel(int x, int y, int colored);
    void DrawShadedPixel(int x, int y);
	void DrawSpeckledPixel(int x, int y, int density=50);
    void DrawCharAt(int x, int y, char ascii_char, sFONT* font, int colored);
    void DrawStringAt(int x, int y, const char* text, sFONT* font, int colored);
    void DrawLine(int x0, int y0, int x1, int y1, int colored);
    void DrawHorizontalLine(int x, int y, int width, int colored);
    void DrawVerticalLine(int x, int y, int height, int colored);
    void DrawRectangle(int x0, int y0, int x1, int y1, int colored);
    void DrawFilledRectangle(int x0, int y0, int x1, int y1, int colored);
    void DrawShadedRectangle(int x0, int y0, int x1, int y1);
	void DrawSpeckledRectangle(int x0, int y0, int x1, int y1, int density=50);
    void DrawCircle(int x, int y, int radius, int colored);
    void DrawFilledCircle(int x, int y, int radius, int colored);
    void DrawShadedCircle(int x, int y, int radius);
	void DrawSpeckledCircle(int x, int y, int radius, int density=50);

private:
    unsigned char* image;
    int width;
    int height;
    int rotate;
};

#endif

/* END OF FILE */

