/*****************************************************************************
* | File        :   LCD_Driver.c
* | Author      :   Waveshare team
* | Function    :   ILI9486 Drive function
* | Info        :
*   Image scanning
*      Please use progressive scanning to generate images or fonts
*----------------
* | This version:   V1.0
* | Date        :   2018-01-11
* | Info        :   Basic version
*
******************************************************************************/
// #include "MicroBitPin.h"
#include "MicroBit.h"
#include "LCD_Driver.h"
#include "SPI_RAM.h"

//spi
// MicroBit uBit;
SPI lcd_spi(MOSI, MISO, SCK);
#define LCD_SPI_Write_Byte(value) lcd_spi.write(value)
MicroBitPin LCD_RST(MICROBIT_ID_IO_P8, MICROBIT_PIN_P8, PIN_CAPABILITY_DIGITAL);
MicroBitPin LCD_DC(MICROBIT_ID_IO_P12, MICROBIT_PIN_P12, PIN_CAPABILITY_DIGITAL);
MicroBitPin LCD_CS(MICROBIT_ID_IO_P16, MICROBIT_PIN_P16, PIN_CAPABILITY_DIGITAL);
// MicroBitPin LCD_CS(MICROBIT_ID_IO_P16, MICROBIT_PIN_P16, PIN_CAPABILITY_DIGITAL);

//LCD
// DigitalOut LCD_RST(MICROBIT_PIN_P8);
// DigitalOut LCD_DC(MICROBIT_PIN_P12);
// DigitalOut LCD_CS(MICROBIT_PIN_P16);
PwmOut LCD_BL(MICROBIT_PIN_P1);

#define LCD_RST_0 LCD_RST = 0
#define LCD_RST_1 LCD_RST = 1
#define LCD_DC_0 LCD_DC = 0
#define LCD_DC_1 LCD_DC = 1
#define LCD_CS_0 LCD_CS = 0
#define LCD_CS_1 LCD_CS = 1

//delay
#define Driver_Delay_ms(xms) wait_ms(xms)

//SPI Ram
SPIRAM *spiram;

/*********************************************
function:
    Initialization system
*********************************************/
void LCD_Driver::LCD_SPI_Init()
{
    lcd_spi.format(8,0);
    lcd_spi.frequency(9000000);
}

/*******************************************************************************
function:
    Hardware reset
*******************************************************************************/
void LCD_Driver::LCD_Reset()
{
    LCD_RST_1;
    Driver_Delay_ms(100);
    LCD_RST_0;
    Driver_Delay_ms(100);
    LCD_RST_1;
    Driver_Delay_ms(100);
}

/*******************************************************************************
function:
    Write register address and data
*******************************************************************************/
void LCD_Driver::LCD_WriteReg(UBYTE Reg)
{
    LCD_DC_0;
    LCD_CS_0;
    LCD_SPI_Write_Byte(Reg);
    LCD_CS_1;
}

void LCD_Driver::LCD_WriteData_8Bit(UBYTE Data)
{
    LCD_DC_1;
    LCD_CS_0;
    LCD_SPI_Write_Byte(Data);
    LCD_CS_1;
}

void LCD_Driver::LCD_WriteData_Buf(UWORD Buf,unsigned long Len)
{
    unsigned long i;
    LCD_DC_1;
    LCD_CS_0;
    for(i = 0; i < Len; i++) {
        LCD_SPI_Write_Byte((int)(Buf >> 8));
        LCD_SPI_Write_Byte((int)(Buf & 0XFF));
    }
    LCD_CS_1;
}
/*******************************************************************************
function:
    Common register initialization
*******************************************************************************/
void LCD_Driver::LCD_InitReg()
{
    //ST7735R Frame Rate
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

    LCD_WriteReg(0xB4); //Column inversion
    LCD_WriteData_8Bit(0x07);

    //ST7735R Power Sequence
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

    LCD_WriteReg(0xC5); //VCOM
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
    LCD_WriteData_8Bit(0xF7 & 0xA0); //RGB color filter panel
}

/********************************************************************************
function:   Sets the start position and size of the display area
parameter:
    Xstart  :   X direction Start coordinates
    Ystart  :   Y direction Start coordinates
    Xend    :   X direction end coordinates
    Yend    :   Y direction end coordinates
********************************************************************************/
void LCD_Driver::LCD_SetWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)
{
    //set the X coordinates
    LCD_WriteReg(0x2A);
    LCD_WriteData_8Bit(0x00);
    LCD_WriteData_8Bit((Xstart & 0xff) + 1);
    LCD_WriteData_8Bit(0x00 );
    LCD_WriteData_8Bit(((Xend - 1) & 0xff) + 1);

    //set the Y coordinates
    LCD_WriteReg(0x2B);
    LCD_WriteData_8Bit(0x00);
    LCD_WriteData_8Bit((Ystart & 0xff) + 2);
    LCD_WriteData_8Bit(0x00 );
    LCD_WriteData_8Bit(((Yend - 1) & 0xff)+ 2);

    LCD_WriteReg(0x2C);
}

/********************************************************************************
function:
    Set the display point (Xpoint, Ypoint)
********************************************************************************/
void LCD_Driver::LCD_SetCursor(UWORD Xpoint, UWORD Ypoint)
{
    LCD_SetWindows(Xpoint, Ypoint, Xpoint, Ypoint);
}

/********************************************************************************
function:
    Set show color
********************************************************************************/
void LCD_Driver::LCD_SetColor(UWORD Color, UWORD Xpoint, UWORD Ypoint)
{
    LCD_WriteData_Buf(Color, (unsigned long)Xpoint * (unsigned long)Ypoint);
}

/********************************************************************************
function:
    initialization
********************************************************************************/
void LCD_Driver::LCD_Init()
{
    LCD_SPI_Init();

    spiram->SPIRAM_SPI_Init();
    spiram->SPIRAM_Set_Mode(BYTE_MODE);

    //back light
    LCD_BL = 1.5;

    //Hardware reset
    LCD_Reset();

    //Set the initialization register
    LCD_InitReg();

    //sleep out
    LCD_WriteReg(0x11);
    Driver_Delay_ms(120);

    //Turn on the LCD display
    LCD_WriteReg(0x29);
}

void LCD_Driver::LCD_SetBL(int Lev)
{
    LCD_BL = Lev / 100;
}

/********************************************************************************
function:
    Clear screen
********************************************************************************/
void LCD_Driver::LCD_Clear(UWORD Color)
{
    LCD_SetWindows(0, 0, LCD_WIDTH, LCD_HEIGHT);
    LCD_SetColor(Color, LCD_WIDTH + 2, LCD_HEIGHT + 2);
}

void LCD_Driver::LCD_ClearBuf()
{
    UWORD x, y;
    UWORD Color = 0xffff;
    for (y = 0; y < 128; y++) {
        for (x = 0; x < 160; x++ ) {//1 pixel = 2 byte
            spiram->SPIRAM_WR_Byte((x + y * 160)* 2, Color >> 8);
            spiram->SPIRAM_WR_Byte((x + y * 160)* 2 + 1, Color);
        }
    }
}

void LCD_Driver::LCD_SetPoint(UWORD Xpoint, UWORD Ypoint, UWORD Color)
{
    UWORD Addr = (Xpoint + Ypoint * 160)* 2;
    spiram->SPIRAM_WR_Byte(Addr, Color >> 8);
    spiram->SPIRAM_WR_Byte(Addr + 1, Color & 0xff);
}

void LCD_Driver::LCD_Display()
{
    UWORD x, y;
    UBYTE RBUF[160 * 2 * 2];//read tow lines
    memset(RBUF, 0xff, sizeof(RBUF));

    spiram->SPIRAM_Set_Mode(STREAM_MODE);
    LCD_SetWindows(0, 0, 160, 128);
    for (y = 0; y < 128 / 2; y++) {//line
        spiram->SPIRAM_RD_Stream(y * 160 * 2 * 2, RBUF, 160 * 2 * 2);

        LCD_DC_1;
        LCD_CS_0;
        for (x = 0; x < 160 * 2; x++ ) {
            LCD_SPI_Write_Byte((uint8_t)RBUF[x * 2]);
            LCD_SPI_Write_Byte((uint8_t)RBUF[x * 2 + 1]);
        }
        LCD_CS_1;
    }
}

void LCD_Driver::LCD_DisplayWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)
{
    UWORD x, y;
    UBYTE RBUF[(Xend - Xstart + 1) * 2];
    memset(RBUF, 0xff, sizeof(RBUF));

    spiram->SPIRAM_Set_Mode(STREAM_MODE);
    LCD_SetWindows(Xstart, Ystart, Xend, Yend);
    for (y = Ystart; y < Yend; y++) {//line
        spiram->SPIRAM_RD_Stream((y * 160 + Xstart) * 2, RBUF, sizeof(RBUF));

        LCD_DC_1;
        LCD_CS_0;
        for (x = 0; x < Xend - Xstart; x++) {
            LCD_SPI_Write_Byte((uint8_t)RBUF[x * 2]);
            LCD_SPI_Write_Byte((uint8_t)RBUF[x * 2 + 1]);
        }
        LCD_CS_1;
    }
}

void LCD_Driver::LCD_DrawPoint(int Xpoint, int Ypoint, DOT_PIXEL Dot_Pixel, int Color)
{
    int XDir_Num ,YDir_Num;
    for(XDir_Num = 0; XDir_Num < Dot_Pixel; XDir_Num++) {
        for(YDir_Num = 0; YDir_Num < Dot_Pixel; YDir_Num++) {
            LCD_SetPoint(Xpoint + XDir_Num - Dot_Pixel, Ypoint + YDir_Num - Dot_Pixel, Color);
        }
    }
}

void LCD_Driver::LCD_DisChar_1207(int Xchar, int Ychar, int Char_Offset, int Color)
{
    int Page = 0, Column = 0;
    const unsigned char *ptr = &Font12_Table[Char_Offset];

    for(Page = 0; Page < 12; Page ++ ) {
        for(Column = 0; Column < 7; Column ++ ) {
            if(*ptr & (0x80 >> (Column % 8)))
                LCD_SetPoint(Xchar + Column, Ychar + Page, Color);

            //One pixel is 8 bits
            if(Column % 8 == 7)
                ptr++;
        }// Write a line
        if(7 % 8 != 0)
            ptr++;
    }// Write all
}