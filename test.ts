// tests go here; this will not be compiled when this package is used as a library

LCD1IN8.LCD_Init()

LCD1IN8.DrawLine(
1,
10,
160,
10,
LCD1IN8.Get_Color(LCD_COLOR.RED),
DOT_PIXEL.DOT_PIXEL_1,
LINE_STYLE.LINE_SOLID
)

LCD1IN8.DrawRectangle(
10,
20,
150,
40,
LCD1IN8.Get_Color(LCD_COLOR.RED),
DRAW_FILL.DRAW_FULL,
DOT_PIXEL.DOT_PIXEL_1
)

LCD1IN8.DisString(
70,
60,
"hello",
LCD1IN8.Get_Color(LCD_COLOR.RED)
)

LCD1IN8.DrawCircle(
50,
50,
5,
LCD1IN8.Get_Color(LCD_COLOR.RED),
DRAW_FILL.DRAW_FULL,
DOT_PIXEL.DOT_PIXEL_1
)


