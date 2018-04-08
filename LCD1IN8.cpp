#include "pxt.h"
#include "LCD_GUI.h"

using namespace pxt;

namespace LCD1IN8 {
	LCD_GUI *lcd;
	
    //%
    void LCD_Init() {
        lcd->GUI_Init();
        lcd->GUI_Clear();
    }
    
    //%
    void SetWindows(int Xstart, int Ystart, int Xend, int Yend) {
        lcd->GUI_SetWindows(Xstart, Ystart, Xend, Yend);
    }
    
    //%
    void SetCursor(int x, int y) {
        lcd->GUI_SetCursor(x, y);
    }
    
    //%
    void SetColor(int Color, int Xpoint, int Ypoint) {
        lcd->GUI_SetColor(Color, Xpoint, Ypoint);
    }
    
    //%
    void DrawPoint(int x, int y, int Color, DOT_PIXEL Dot) {
        lcd->GUI_DrawPoint(x, y, Dot, Color);
    }
    
    //%
    int GetFontData(CHARFONT chfont, int Offset) {
        return lcd->GUI_GetFontData(chfont, Offset);
    }
    
    //%
    int GetFontHeight(CHARFONT chfont) {
        return lcd->GUI_GetFontHeight(chfont);
    }
    
    //%
    int GetFontWidth(CHARFONT chfont) {
        return lcd->GUI_GetFontWidth(chfont);
    }

}

