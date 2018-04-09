#include "LCD_GUI.h"
#include "LCD_Driver.h"

LCD_DRIVER *lcd1in8;

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
	int Page = 0, Column = 0;
	const unsigned char *ptr = &Font12_Table[Char_Offset];

    for(Page = 0; Page < 12; Page ++ ) {
        for(Column = 0; Column < 7; Column ++ ) {
            if(*ptr & (0x80 >> (Column % 8)))
                lcd1in8->LCD_SetPointlColor(Xchar + Column, Ychar + Page, Color);

            //One pixel is 8 bits
            if(Column % 8 == 7)
                ptr++;
        }// Write a line
        if(7 % 8 != 0)
            ptr++;
    }// Write all
}