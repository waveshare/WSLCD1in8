#ifndef _LCD_GUI_H_
#define _LCD_GUI_H_

#include "LCD_Driver.h"

enum LCD_COLOR {
    WHITE = 0xFFFF,
    BLACK = 0x0000,
    BLUE = 0x001F,
    BRED = 0XF81F,
    GRED = 0XFFE0,
    GBLUE = 0X07FF,
    RED = 0xF800,
    MAGENTA = 0xF81F,
    GREEN = 0x07E0,
    CYAN = 0x7FFF,
    YELLOW = 0xFFE0,
    BROWN = 0XBC40,
    BRRED = 0XFC07,
    GRAY = 0X8430
};

enum DOT_PIXEL{
    DOT_PIXEL_1 = 1,
    DOT_PIXEL_2,
    DOT_PIXEL_3,
    DOT_PIXEL_4
};

enum LINE_STYLE {
    LINE_SOLID = 0,
    LINE_DOTTED,
};

enum DRAW_FILL {
    DRAW_EMPTY = 0,
    DRAW_FULL,
};

enum CHARFONT{
    CH_font8 = 0,
    CH_font12,
    CH_font16
};


class LCD_GUI{
public:
    void GUI_Init(void);
    void GUI_Clear(void);
    
    void GUI_SetWindows(int Xstart, int Ystart, int Xend, int Yend) ;
    void GUI_SetCursor(int x, int y);
    void GUI_SetColor(int Color, int Xpoint, int Ypoint);
    
    void GUI_DrawPoint(int Xpoint, int Ypoint, DOT_PIXEL Dot_Pixel, int Color);
    int GUI_GetFontData(CHARFONT chfont, int Offset);
    int GUI_GetFontHeight(CHARFONT chfont);
    int GUI_GetFontWidth(CHARFONT chfont);
    
};

#endif