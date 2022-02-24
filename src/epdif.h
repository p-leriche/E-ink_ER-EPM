/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/

#ifndef EPDIF_H
#define EPDIF_H

#include <arduino.h>

// Pin definition
#define RST_PIN         8
#define DC_PIN          9
#define CS_PIN          10
#define BUSY_PIN        7

class EpdIf {
public:
    EpdIf(void);
    ~EpdIf(void);

    int  IfInit(void);
    void DigitalWrite(int pin, int value); 
    int  DigitalRead(int pin);
    void DelayMs(unsigned int delaytime);
    void SpiTransfer(unsigned char data);
	
    unsigned int busy_pin;
    unsigned int reset_pin;
    unsigned int dc_pin;
    unsigned int cs_pin;
};

#endif
