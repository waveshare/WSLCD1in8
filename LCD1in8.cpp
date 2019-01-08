#include "pxt.h"
#include "LCD_Driver.h"

using namespace pxt;

//% weight=20 color=#436EEE icon="\uf108"
namespace LCD1IN8 {
	LCD_Driver *LCD;
	
    //%
    void LCD_Init() {
        LCD->LCD_Init();
    }
	
    //%
    void LCD_Clear() {
        LCD->LCD_Clear(WHITE);
		LCD->LCD_ClearBuf();
    }
    
    //%
    void LCD_Filling(int Color) {
        LCD->LCD_Clear(Color);
    }
	
	//%
    void LCD_Display() {
        LCD->LCD_Display();
    }
    
    //%
    void LCD_DisplayWindows(int Xstart, int Ystart, int Xend, int Yend) {
        LCD->LCD_DisplayWindows(Xstart, Ystart, Xend, Yend);
    }
	
	//%
    void LCD_SetBL(int Lev) {
        LCD->LCD_SetBL(Lev);
    }
	
    //%
    void DrawPoint(int x, int y, int Color, int Dot) {
        LCD->LCD_DrawPoint(x, y, Color, Dot);
    }

    //%
    void DisChar_1207(int Xchar, int Ychar, int Char_Offset, int Color){
        LCD->LCD_DisChar_1207(Xchar, Ychar, Char_Offset, Color);
    }
}

