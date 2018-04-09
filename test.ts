// tests go here; this will not be compiled when this package is used as a library

LCD1IN8.LCD_Init()

LCD1IN8.DrawLine(
10,
10,
120,
10,
LCD1IN8.Get_Color(LCD_COLOR.RED),
DOT_PIXEL.DOT_PIXEL_1,
LINE_STYLE.LINE_SOLID
)

LCD1IN8.DrawRectangle(
10,
20,
120,
40,
LCD1IN8.Get_Color(LCD_COLOR.RED),
DRAW_FILL.DRAW_FULL,
DOT_PIXEL.DOT_PIXEL_1
)

LCD1IN8.DisString(
10,
50,
"hello",
LCD1IN8.Get_Color(LCD_COLOR.RED)
)
