#include "LCD_GUI.h"
#include "LCD_Driver.h"
//#include "fonts.h"

LCD_DRIVER *lcd1in8;
//sFONT* Font;

void LCD_GUI::GUI_Init(void){
    lcd1in8->LCD_Init();
}

void LCD_GUI::GUI_Clear(void){
    lcd1in8->LCD_Clear();
}

void LCD_GUI::GUI_SetWindows(int Xstart, int Ystart, int Xend, int Yend) {
    lcd1in8->LCD_SetWindows(Xstart, Ystart, Xend, Yend);
}

void LCD_GUI::GUI_SetCursor(int x, int y) {
    lcd1in8->LCD_SetCursor(x, y);
}

void LCD_GUI::GUI_SetColor(int Color, int Xpoint, int Ypoint) {
    lcd1in8->LCD_SetColor(Color, Xpoint, Ypoint);
}

/********************************************************************************
function:   Draw int(Xpoint, Ypoint) Fill the color
parameter:
            Xpoint      :   The x coordinate of the int
            Ypoint      :   The y coordinate of the int
            Color       :   Set color
            Dot_Pixel   :   int size
********************************************************************************/
void LCD_GUI::GUI_DrawPoint(int Xpoint, int Ypoint, DOT_PIXEL Dot_Pixel, int Color){
    int XDir_Num ,YDir_Num;
    for(XDir_Num = 0; XDir_Num < Dot_Pixel; XDir_Num++) {
        for(YDir_Num = 0; YDir_Num < Dot_Pixel; YDir_Num++) {
            lcd1in8->LCD_SetPointlColor(Xpoint + XDir_Num - Dot_Pixel, Ypoint + YDir_Num - Dot_Pixel, Color);
        }
    }
}

void LCD_GUI::GUI_DisChar(int Xchar, int Ychar, int Char_Offset, int Color){
    if(Char_Offset == 97){        
        GUI_DrawPoint(Xchar, Ychar, DOT_PIXEL_2, Color);
    }else{
        GUI_DrawPoint(Xchar, Ychar, DOT_PIXEL_3, 0xF800);
    }
}