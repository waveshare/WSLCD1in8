/*****************************************************************************
* | File        :   test.ts
* | Author      :   Waveshare team
* | Function    :   FM25V05 DRIVER
* | Info        :
*----------------
* | This version:   V1.0
* | Date        :   2017-12-12
* | Info        :   Basic version
*
******************************************************************************/
// tests go here; this will not be compiled when this package is used as a library
LCD1IN8.LCD_Init()
LCD1IN8.LCD_SetBL(180)
LCD1IN8.LCD_Filling(LCD_COLOR.RED)
LCD1IN8.LCD_Clear()
LCD1IN8.DrawLine(
1,
1,
160,
1,
LCD1IN8.Get_Color(LCD_COLOR.BLUE),
DOT_PIXEL.DOT_PIXEL_2,
LINE_STYLE.LINE_SOLID
)
LCD1IN8.DrawLine(
1,
7,
160,
7,
LCD1IN8.Get_Color(LCD_COLOR.RED),
DOT_PIXEL.DOT_PIXEL_1,
LINE_STYLE.LINE_DOTTED
)
LCD1IN8.DrawLine(
1,
1,
160,
1,
LCD1IN8.Get_Color(LCD_COLOR.BLUE),
DOT_PIXEL.DOT_PIXEL_2,
LINE_STYLE.LINE_SOLID
)
LCD1IN8.DrawRectangle(
5,
10,
155,
60,
LCD1IN8.Get_Color(LCD_COLOR.GBLUE),
DRAW_FILL.DRAW_EMPTY,
DOT_PIXEL.DOT_PIXEL_1
)
LCD1IN8.DrawRectangle(
10,
15,
150,
30,
LCD1IN8.Get_Color(LCD_COLOR.MAGENTA),
DRAW_FILL.DRAW_FULL,
DOT_PIXEL.DOT_PIXEL_1
)
LCD1IN8.DrawCircle(
30,
45,
10,
LCD1IN8.Get_Color(LCD_COLOR.GREEN),
DRAW_FILL.DRAW_EMPTY,
DOT_PIXEL.DOT_PIXEL_1
)
LCD1IN8.DrawCircle(
60,
45,
10,
LCD1IN8.Get_Color(LCD_COLOR.BLUE),
DRAW_FILL.DRAW_FULL,
DOT_PIXEL.DOT_PIXEL_1
)
LCD1IN8.DisString(
6,
65,
"Waveshare electronics",
LCD1IN8.Get_Color(LCD_COLOR.BLUE)
)
LCD1IN8.DisString(
0,
75,
"1.8inch LCD for micro:bit 160*128 pixel,262K Color,ST7735S controller,RAM 23LC1024",
LCD1IN8.Get_Color(LCD_COLOR.RED)
)
LCD1IN8.LCD_Display()


