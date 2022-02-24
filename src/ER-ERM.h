/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/

#ifndef EPD1IN54C_H
#define EPD1IN54C_H

#include "epdif.h"

// Display resolution
#define EPD_WIDTH       152
#define EPD_HEIGHT      152


#define PANEL_SETTING                               0x00
#define POWER_SETTING                               0x01
#define POWER_OFF                                   0x02
#define POWER_OFF_SEQUENCE_SETTING                  0x03
#define POWER_ON                                    0x04
#define POWER_ON_MEASURE                            0x05
#define BOOSTER_SOFT_START                          0x06
#define DEEP_SLEEP                                  0x07
#define DATA_START_TRANSMISSION_1                   0x10
#define DATA_STOP                                   0x11
#define DISPLAY_REFRESH                             0x12
#define DATA_START_TRANSMISSION_2                   0x13
#define PLL_CONTROL                                 0x30
#define TEMPERATURE_SENSOR_COMMAND                  0x40
#define TEMPERATURE_SENSOR_CALIBRATION              0x41
#define TEMPERATURE_SENSOR_WRITE                    0x42
#define TEMPERATURE_SENSOR_READ                     0x43
#define VCOM_AND_DATA_INTERVAL_SETTING              0x50
#define LOW_POWER_DETECTION                         0x51
#define TCON_SETTING                                0x60
#define TCON_RESOLUTION                             0x61
#define SOURCE_AND_GATE_START_SETTING               0x62
#define GET_STATUS                                  0x71
#define AUTO_MEASURE_VCOM                           0x80
#define VCOM_VALUE                                  0x81
#define VCM_DC_SETTING_REGISTER                     0x82
#define PARTIAL_WINDOW                              0x90
#define PARTIAL_IN                                  0x91
#define PARTIAL_OUT                                 0x92
#define PROGRAM_MODE                                0xA0
#define ACTIVE_PROGRAMMING                          0xA1
#define READ_OTP                                    0xA2
#define POWER_SAVING                                0xE3

extern const unsigned char lut_vcom0[];
extern const unsigned char lut_vcom1[];
extern const unsigned char lut_w[];
extern const unsigned char lut_b[];
extern const unsigned char lut_g1[];
extern const unsigned char lut_g2[];
extern const unsigned char lut_red0[];
extern const unsigned char lut_red1[];

class Epd : EpdIf {
public:
    unsigned long width;
    unsigned long height;

    Epd(int Width = EPD_WIDTH, int Height = EPD_HEIGHT,
      int Busy_Pin = BUSY_PIN, int Reset_Pin = RST_PIN, int Dc_pin = DC_PIN, int Cs_pin=CS_PIN);
    ~Epd();
    int  Init(void);
    void SendCommand(unsigned char command);
    void SendData(unsigned char data);
    void WaitUntilIdle(void);
    void Reset(void);
    void SetLutBw(void);
    void SetLutRed(void);
    void SetPartialWindow(const unsigned char* buffer_black, const unsigned char* buffer_red, int x, int y, int w, int l);
    void SetPartialWindowBlack(const unsigned char* buffer_black, int x, int y, int w, int l);
    void SetPartialWindowRed(const unsigned char* buffer_red, int x, int y, int w, int l);
    void DisplayFrame(void);
    void ClearFrame(void);
    
    void DisplayFrame(const unsigned char* frame_buffer_black, const unsigned char* frame_buffer_red);
    void Sleep(void);
};

#endif 

/* END OF FILE */
