/*****************************************************************************
* | File      	:   WS1in8LCD
* | Author      :   Waveshare team
* | Function    :   Contorl lcd Show
* | Info        :
*----------------
* | This version:   V1.0
* | Date        :   2018-02-22
* | Info        :   Basic version
*
******************************************************************************/
let GUI_BACKGROUND_COLOR = LCD_COLOR.WHITE
let FONT_BACKGROUND_COLOR = LCD_COLOR.WHITE
let FONT_FOREGROUND_COLOR = LCD_COLOR.BLACK


//% weight=20 color=#436EEE icon="\uf108"
namespace LCD1IN8 {
    function Swop_AB(Point1: number, Point2: number): void {
        let Temp = 0;
        Temp = Point1;
        Point1 = Point2;
        Point2 = Temp;
    }
        
    //% shim=LCD1IN8::SetWindows
    function SetWindows(Xstart: number, Ystart: number, Xend: number, Yend: number): void{
        return;
    }
    
    //% shim=LCD1IN8::SetCursor
    function SetCursor(x: number, y: number): void{
        return;
    }
    
    //% shim=LCD1IN8::SetColor
    function SetColor(Color: number, x: number, y: number): void{
        return;
    }

    //% blockId=LCD_Init
    //% blockGap=8
    //% block="LCD1IN8 Init"
    //% shim=LCD1IN8::LCD_Init
    //% weight=200
    export function LCD_Init(): void{
        return;
    }
    
    //% blockId=Get_Color
    //% blockGap=8
    //% block="%Color"
    //% weight=199
    export function Get_Color(Color: LCD_COLOR): number{
        return Color;
    }
    
    //% blockId=DrawPoint
    //% blockGap=8
    //% block="Draw Point|x %x|y %y|Color %Color|Point Size %Dot"
    //% x.min=0 x.max=160 y.min=0 y.max=128
    //% Color.min=0 Color.max=65535
    //% shim=LCD1IN8::DrawPoint
    //% weight=190
    export function DrawPoint(x: number, y: number, Color: number, Dot: DOT_PIXEL): void{
        return;
    }

    /*
    * Draw a line of arbitrary slope
    */
    //% blockId=DrawLine
    //% blockGap=8
    //% block="Draw Line|Xstart %Xstart|Ystart %Ystart|Xend %Xend|Yend %Yend|Color %Color|Line width %Line_width|Line Style %Line_Style"
    //% Xstart.min=0 Xstart.max=160 Ystart.min=0 Ystart.max=128
    //% Xend.min=0 Xend.max=160 Yend.min=0 Yend.max=128
    //% Color.min=0 Color.max=65535
    //% weight=180
    export function DrawLine(Xstart: number, Ystart: number, Xend: number, Yend: number, Color: number, Line_width: DOT_PIXEL, Line_Style: LINE_STYLE): void {
        if (Xstart > Xend)
            Swop_AB(Xstart, Xend);
        if (Ystart > Yend)
            Swop_AB(Ystart, Yend);

        let Xpoint = Xstart;
        let Ypoint = Ystart;
        let dx = Xend - Xstart >= 0 ? Xend - Xstart : Xstart - Xend;
        let dy = Yend - Ystart <= 0 ? Yend - Ystart : Ystart - Yend;

        // Increment direction, 1 is positive, -1 is counter;
        let XAddway = Xstart < Xend ? 1 : -1;
        let YAddway = Ystart < Yend ? 1 : -1;

        //Cumulative error
        let Esp = dx + dy;
        let Line_Style_Temp = 0;

        for (; ;) {
            Line_Style_Temp++;
            //Painted dotted line, 2 point is really virtual
            if (Line_Style == LINE_STYLE.LINE_DOTTED && Line_Style_Temp % 3 == 0) {
                DrawPoint(Xpoint, Ypoint, GUI_BACKGROUND_COLOR, Line_width);
                Line_Style_Temp = 0;
            } else {
                DrawPoint(Xpoint, Ypoint, Color, Line_width);
            }
            if (2 * Esp >= dy) {
                if (Xpoint == Xend) break;
                Esp += dy
                Xpoint += XAddway;
            }
            if (2 * Esp <= dx) {
                if (Ypoint == Yend) break;
                Esp += dx;
                Ypoint += YAddway;
            }
        }
    }
    
    /*
    * Draw a rectangle
    */
    //% blockId=DrawRectangle
    //% blockGap=8
    //% block="Draw Rectangle|Xstart2 %Xstart2|Ystart2 %Ystart2|Xend2 %Xend2|Yend2 %Yend2|Color %Color|Filled %Filled |Line width %Dot_Pixel"
    //% Xstart2.min=0 Xstart2.max=160 Ystart2.min=0 Ystart2.max=128 
    //% Xend2.min=0 Xend2.max=160 Yend2.min=0 Yend2.max=128
    //% Color.min=0 Color.max=65535
    //% weight=170
    export function DrawRectangle(Xstart2: number, Ystart2: number, Xend2: number, Yend2: number, Color: number, Filled: DRAW_FILL, Dot_Pixel: DOT_PIXEL): void {
        if (Xstart2 > Xend2)
            Swop_AB(Xstart2, Xend2);
        if (Ystart2 > Yend2)
            Swop_AB(Ystart2, Yend2);

        let Ypoint = 0;
        if (Filled) {
            SetWindows(Xstart2, Ystart2, Xend2, Yend2);
            SetColor(Color, Yend2 - Ystart2, Xend2 - Xstart2);
        } else {
            DrawLine(Xstart2, Ystart2, Xend2, Ystart2, Color, Dot_Pixel, LINE_STYLE.LINE_SOLID);
            DrawLine(Xstart2, Ystart2, Xstart2, Yend2, Color, Dot_Pixel, LINE_STYLE.LINE_SOLID);
            DrawLine(Xend2, Yend2, Xend2, Ystart2, Color, Dot_Pixel, LINE_STYLE.LINE_SOLID);
            DrawLine(Xend2, Yend2, Xstart2, Yend2, Color, Dot_Pixel, LINE_STYLE.LINE_SOLID);
        }
    }

    /*
    * Use the 8-point method to draw a circle of the
    */
    //% blockId=DrawCircle
    //% blockGap=8
    //% block="Draw Circle|X_Center %X_Center |Y_Center %Y_Center |Radius %Radius|Color %Color|Filled %Draw_Fill|Line width %Dot_Pixel "
    //% X_Center.min=0 X_Center.max=160 
    //% Y_Center.min=0 Y_Center.max=64 
    //% Radius.min=0 Radius.max=64 
    //% Color.min=0 Color.max=65535
    //% weight=160
    export function DrawCircle(X_Center: number, Y_Center: number, Radius: number, Color: number, Draw_Fill: DRAW_FILL, Dot_Pixel: DOT_PIXEL): void {
        //Draw a circle from(0, R) as a starting point
        let XCurrent = 0;
        let YCurrent = Radius;

        //Cumulative error,judge the next point of the logo
        let Esp = 3 - (Radius << 1);

        let sCountY = 0;
        if (Draw_Fill == DRAW_FILL.DRAW_FULL) {
            while (XCurrent <= YCurrent) { //Realistic circles
                for (sCountY = XCurrent; sCountY <= YCurrent; sCountY++) {
                    DrawPoint(X_Center + XCurrent, Y_Center + sCountY, DOT_PIXEL.DOT_PIXEL_1, Color);             //1
                    DrawPoint(X_Center - XCurrent, Y_Center + sCountY, DOT_PIXEL.DOT_PIXEL_1, Color);             //2
                    DrawPoint(X_Center - sCountY, Y_Center + XCurrent, DOT_PIXEL.DOT_PIXEL_1, Color);             //3
                    DrawPoint(X_Center - sCountY, Y_Center - XCurrent, DOT_PIXEL.DOT_PIXEL_1, Color);             //4
                    DrawPoint(X_Center - XCurrent, Y_Center - sCountY, DOT_PIXEL.DOT_PIXEL_1, Color);             //5
                    DrawPoint(X_Center + XCurrent, Y_Center - sCountY, DOT_PIXEL.DOT_PIXEL_1, Color);             //6
                    DrawPoint(X_Center + sCountY, Y_Center - XCurrent, DOT_PIXEL.DOT_PIXEL_1, Color);             //7
                    DrawPoint(X_Center + sCountY, Y_Center + XCurrent, DOT_PIXEL.DOT_PIXEL_1, Color);
                }
                if (Esp < 0)
                    Esp += 4 * XCurrent + 6;
                else {
                    Esp += 10 + 4 * (XCurrent - YCurrent);
                    YCurrent--;
                }
                XCurrent++;
            }
        } else { //Draw a hollow circle
            while (XCurrent <= YCurrent) {
                DrawPoint(X_Center + XCurrent, Y_Center + YCurrent, Dot_Pixel, Color);             //1
                DrawPoint(X_Center - XCurrent, Y_Center + YCurrent, Dot_Pixel, Color);             //2
                DrawPoint(X_Center - YCurrent, Y_Center + XCurrent, Dot_Pixel, Color);             //3
                DrawPoint(X_Center - YCurrent, Y_Center - XCurrent, Dot_Pixel, Color);             //4
                DrawPoint(X_Center - XCurrent, Y_Center - YCurrent, Dot_Pixel, Color);             //5
                DrawPoint(X_Center + XCurrent, Y_Center - YCurrent, Dot_Pixel, Color);             //6
                DrawPoint(X_Center + YCurrent, Y_Center - XCurrent, Dot_Pixel, Color);             //7
                DrawPoint(X_Center + YCurrent, Y_Center + XCurrent, Dot_Pixel, Color);             //0

                if (Esp < 0)
                    Esp += 4 * XCurrent + 6;
                else {
                    Esp += 10 + 4 * (XCurrent - YCurrent);
                    YCurrent--;
                }
                XCurrent++;
            }
        }
    }

    //% shim=LCD1IN8::DistChar
    function DistChar(Xchar: number, Ychar: number, Char_Offset: number, Color: number): void{
        return;
    }

    //% blockId=DisString
    //% blockGap=8
    //% block="Show String|X %Xchar|Y %Ychar|char %ch|Foreground %Color"
    //% Xchar.min=0 Xchar.max=160 Ychar.min=0 Ychar.max=64 
    //% Color.min=0 Color.max=65535
    //% weight=140
    export function DisString(Xchar: number, Ychar: number, ch: string, Color: number): void{
        return;
        let Font_Height = 12;//GetFontHeight(chfont);
        let Font_Width = 7;//GetFontWidth(chfont);

        let ch_asicc =  ch.charCodeAt(0);
        let Char_Offset = ch_asicc * Font_Height *(Font_Width / 8 +(Font_Width % 8 ? 1 : 0));
        
        DistChar(Xchar, Ychar, Char_Offset, Color);
        /*serial.writeNumber(ptr);
            
        let Page = 0;
        let Column = 0;
        for(Page = 0; Page < Font_Height; Page ++ ) {
            for(Column = 0; Column < Font_Width; Column ++ ) {
                if(FONT_BACKGROUND_COLOR == Color_Background) {
                    if(ptr &(0x80 >>(Column % 8)))
                        DrawPoint(Xchar + Column, Ychar + Page, Color_Foreground, DOT_PIXEL.DOT_PIXEL_1);
                } else {
                    if(ptr &(0x80 >>(Column % 8))) {
                        DrawPoint(Xchar + Column, Ychar + Page, Color_Foreground, DOT_PIXEL.DOT_PIXEL_1);
                    } else {
                        DrawPoint(Xchar + Column, Ychar + Page, Color_Background, DOT_PIXEL.DOT_PIXEL_1);
                    }
                }
                //One pixel is 8 bits
                if(Column % 8 == 7)
                    ptr = GetFontData(chfont, Char_Offset + 1);
            }// Write a line
            if(Font_Width % 8 != 0)
                ptr = GetFontData(chfont, Char_Offset + 1);
        }// Write all
        */
    }
}
