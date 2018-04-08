// tests go here; this will not be compiled when this package is used as a library

LCD1IN8.LCD_Init()

LCD1IN8.DrawLine(
42,
54,
73,
32,
LCD1IN8.Get_Color(LCD_COLOR.RED),
DOT_PIXEL.DOT_PIXEL_1,
LINE_STYLE.LINE_DOTTED
)

LCD1IN8.DrawRectangle(
10,
10,
30,
30,
LCD1IN8.Get_Color(LCD_COLOR.RED),
DRAW_FILL.DRAW_FULL,
DOT_PIXEL.DOT_PIXEL_1
)
