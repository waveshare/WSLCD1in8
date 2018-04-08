#include "MicroBitPin.h"
#include "mbed.h"
#include "LCD_Driver.h"

//spi
SPI spi(MOSI, MISO, SCK);

//gpio
DigitalOut LCD_RST(MICROBIT_PIN_P8);
DigitalOut LCD_DC(MICROBIT_PIN_P12);
DigitalOut LCD_CS(MICROBIT_PIN_P16);

#define LCD_RST_0 LCD_RST = 0
#define LCD_RST_1 LCD_RST = 1
#define LCD_DC_0 LCD_DC = 0
#define LCD_DC_1 LCD_DC = 1
#define LCD_CS_0 LCD_CS = 0
#define LCD_CS_1 LCD_CS = 1

void LCD_DRIVER::LCD_Reset(void){
    LCD_RST_1;
    wait_ms(100);
    LCD_RST_0;
    wait_ms(100);
    LCD_RST_1;
    wait_ms(100);
}

/*******************************************************************************
function:
    Write register address and data
*******************************************************************************/
void LCD_DRIVER::LCD_WriteReg(unsigned char Reg){
    LCD_DC_0;
    LCD_CS_0;
    spi.write(Reg);
    LCD_CS_1;
}

void LCD_DRIVER::LCD_WriteData_8Bit(unsigned char Data){
    LCD_DC_1;
    LCD_CS_0;
    spi.write(Data);
    LCD_CS_1;
}

void LCD_DRIVER::LCD_WriteData_16Bit(unsigned int Data,unsigned short Xdir, unsigned short Ydir){
    unsigned short x, y;
    LCD_DC_1;
    LCD_CS_0;
    for(y = 0; y < Ydir; y++) {
        for(x = 0; x < Xdir; x++) {
            spi.write((unsigned char)(Data >> 8));
            spi.write((unsigned char)(Data & 0XFF));
        }
    }
    LCD_CS_1;
}

void LCD_DRIVER::LCD_InitReg(void){
    LCD_WriteReg(0xB1);
    LCD_WriteData_8Bit(0x01);
    LCD_WriteData_8Bit(0x2C);
    LCD_WriteData_8Bit(0x2D);

    LCD_WriteReg(0xB2);
    LCD_WriteData_8Bit(0x01);
    LCD_WriteData_8Bit(0x2C);
    LCD_WriteData_8Bit(0x2D);

    LCD_WriteReg(0xB3);
    LCD_WriteData_8Bit(0x01);
    LCD_WriteData_8Bit(0x2C);
    LCD_WriteData_8Bit(0x2D);
    LCD_WriteData_8Bit(0x01);
    LCD_WriteData_8Bit(0x2C);
    LCD_WriteData_8Bit(0x2D);

    LCD_WriteReg(0xB4); 
    LCD_WriteData_8Bit(0x07);
    
    LCD_WriteReg(0xC0);
    LCD_WriteData_8Bit(0xA2);
    LCD_WriteData_8Bit(0x02);
    LCD_WriteData_8Bit(0x84);
    LCD_WriteReg(0xC1);
    LCD_WriteData_8Bit(0xC5);

    LCD_WriteReg(0xC2);
    LCD_WriteData_8Bit(0x0A);
    LCD_WriteData_8Bit(0x00);

    LCD_WriteReg(0xC3);
    LCD_WriteData_8Bit(0x8A);
    LCD_WriteData_8Bit(0x2A);
    LCD_WriteReg(0xC4);
    LCD_WriteData_8Bit(0x8A);
    LCD_WriteData_8Bit(0xEE);

    LCD_WriteReg(0xC5); 
    LCD_WriteData_8Bit(0x0E);
    
    //ST7735R Gamma Sequence
    LCD_WriteReg(0xe0);
    LCD_WriteData_8Bit(0x0f);
    LCD_WriteData_8Bit(0x1a);
    LCD_WriteData_8Bit(0x0f);
    LCD_WriteData_8Bit(0x18);
    LCD_WriteData_8Bit(0x2f);
    LCD_WriteData_8Bit(0x28);
    LCD_WriteData_8Bit(0x20);
    LCD_WriteData_8Bit(0x22);
    LCD_WriteData_8Bit(0x1f);
    LCD_WriteData_8Bit(0x1b);
    LCD_WriteData_8Bit(0x23);
    LCD_WriteData_8Bit(0x37);
    LCD_WriteData_8Bit(0x00);
    LCD_WriteData_8Bit(0x07);
    LCD_WriteData_8Bit(0x02);
    LCD_WriteData_8Bit(0x10);

    LCD_WriteReg(0xe1);
    LCD_WriteData_8Bit(0x0f);
    LCD_WriteData_8Bit(0x1b);
    LCD_WriteData_8Bit(0x0f);
    LCD_WriteData_8Bit(0x17);
    LCD_WriteData_8Bit(0x33);
    LCD_WriteData_8Bit(0x2c);
    LCD_WriteData_8Bit(0x29);
    LCD_WriteData_8Bit(0x2e);
    LCD_WriteData_8Bit(0x30);
    LCD_WriteData_8Bit(0x30);
    LCD_WriteData_8Bit(0x39);
    LCD_WriteData_8Bit(0x3f);
    LCD_WriteData_8Bit(0x00);
    LCD_WriteData_8Bit(0x07);
    LCD_WriteData_8Bit(0x03);
    LCD_WriteData_8Bit(0x10);

    LCD_WriteReg(0xF0); //Enable test command
    LCD_WriteData_8Bit(0x01);

    LCD_WriteReg(0xF6); //Disable ram power save mode
    LCD_WriteData_8Bit(0x00);

    LCD_WriteReg(0x3A); //65k mode
    LCD_WriteData_8Bit(0x05);
    
    LCD_WriteReg(0x36); //MX, MY, RGB mode
    LCD_WriteData_8Bit(0x60);

}

void LCD_DRIVER::LCD_Init(void){
    //Hardware reset
    LCD_Reset();

    //Set the initialization register
    LCD_InitReg();

    //sleep out
    LCD_WriteReg(0x11);
    wait_ms(100);

    //Turn on the LCD LCD_DRIVER
    LCD_WriteReg(0x29);
}

/********************************************************************************
function:   Sets the start position and size of the area
parameter:
    Xstart  :   X direction Start coordinates
    Ystart  :   Y direction Start coordinates
    Xend    :   X direction end coordinates
    Yend    :   Y direction end coordinates
********************************************************************************/
void LCD_DRIVER::LCD_SetWindows(POINT Xstart, POINT Ystart, POINT Xend, POINT Yend){
    //set the X coordinates
    LCD_WriteReg(0x2A);
    LCD_WriteData_8Bit(0x00); 
    LCD_WriteData_8Bit((Xstart & 0xff) + 2); 
    LCD_WriteData_8Bit(0x00 ); 
    LCD_WriteData_8Bit(((Xend - 1) & 0xff) + 2); 

    //set the Y coordinates
    LCD_WriteReg(0x2B);
    LCD_WriteData_8Bit(0x00);
    LCD_WriteData_8Bit((Ystart & 0xff) + 3);
    LCD_WriteData_8Bit(0x00 );
    LCD_WriteData_8Bit(((Yend - 1) & 0xff)+ 3);

    LCD_WriteReg(0x2C);
}

/********************************************************************************
function:   Set the point (Xpoint, Ypoint)
parameter:
    xStart :   X direction Start coordinates
    xEnd   :   X direction end coordinates
********************************************************************************/
void LCD_DRIVER::LCD_SetCursor(POINT Xpoint, POINT Ypoint){
    LCD_SetWindows(Xpoint, Ypoint, Xpoint, Ypoint);
}

/********************************************************************************
function:   Set show color
parameter:
    Color  :   Set show color
********************************************************************************/
void LCD_DRIVER::LCD_SetColor(COLOR Color, POINT Xpoint, POINT Ypoint){
    LCD_WriteData_16Bit(Color, Xpoint, Ypoint);
}

/********************************************************************************
function:   Point (Xpoint, Ypoint) Fill the color
parameter:
    Xpoint :   The x coordinate of the point
    Ypoint :   The y coordinate of the point
    Color  :   Set the color
********************************************************************************/
void LCD_DRIVER::LCD_SetPointlColor(POINT Xpoint, POINT Ypoint, COLOR Color){
    if ((Xpoint < LCD_WIDTH) && (Ypoint < LCD_HEIGHT)){
        LCD_SetCursor(Xpoint, Ypoint);
        LCD_SetColor(Color, 1, 1);
    }
}

/********************************************************************************
function:   Fill the area with the color
parameter:
    Xstart :   Start point x coordinate
    Ystart :   Start point y coordinate
    Xend   :   End point coordinates
    Yend   :   End point coordinates
    Color  :   Set the color
********************************************************************************/
void LCD_DRIVER::LCD_SetArealColor(POINT Xstart, POINT Ystart, POINT Xend, POINT Yend, COLOR Color){
    if((Xend > Xstart) && (Yend > Ystart)) {
        LCD_SetWindows(Xstart, Ystart, Xend, Yend);
        LCD_SetColor(Color, Xend - Xstart, Yend - Ystart);
    }
}

/********************************************************************************
function:
    Clear screen
********************************************************************************/
void LCD_DRIVER::LCD_Clear(void){
    LCD_SetArealColor(0,0, LCD_WIDTH + 1, LCD_HEIGHT + 2, 0xffff);
}
