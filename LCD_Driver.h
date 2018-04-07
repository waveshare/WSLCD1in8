#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_

#define COLOR   unsigned short
#define POINT   int
#define LENGTH  int

#define LCD_WIDTH  160  //LCD width
#define LCD_HEIGHT  128 //LCD height

class LCD_DRIVER{
public:
    void LCD_Reset(void);
    
    void LCD_WriteReg(unsigned char Reg);
    void LCD_WriteData_8Bit(unsigned char Data);  
    void LCD_WriteData_16Bit(unsigned int Data,unsigned short Xdir, unsigned short Ydir);

    void LCD_InitReg(void);
    void LCD_Init(void);
      
    void LCD_SetWindows(POINT Xstart, POINT Ystart, POINT Xend, POINT Yend);
    void LCD_SetCursor(POINT Xpoint, POINT Ypoint);
    void LCD_SetColor(COLOR Color, POINT Xpoint, POINT Ypoint);
    void LCD_SetPointlColor(POINT Xpoint, POINT Ypoint, COLOR Color);
    void LCD_SetArealColor(POINT Xstart, POINT Ystart, POINT Xend, POINT Yend, COLOR Color);
    
    void LCD_Clear(void);
};


#endif