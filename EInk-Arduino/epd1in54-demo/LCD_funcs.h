/**
 *  @filename   :   imagedata.h
 *  @brief      :   head file for imagedata.cpp
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef LCD_FUNCS_H
#define LCD_FUNCS_H

#include <epd1in54.h>
#include <epdpaint.h>
#include <fonts.h>

#define COLORED     0
#define UNCOLORED   1

#define BUTTON_SIZE0    0
#define BUTTON_SIZE1    1
#define BUTTON_SIZE2    2
#define BUTTON_SIZE3    3
#define BUTTON_SIZE4    4


void LCD_SetArea(Paint* LCDScreen, int Xpos, int Ypos, int ROTATION_DEGREE);
void LCD_DrawString(Paint* LCDScreen, Epd* LCDMemory, int x, int y, const char* STRING, int FontSize, int colored);
void LCD_LoadImage(Epd* LCDMemory, const unsigned char* image_buffer);
bool LCD_Test(Epd LCDMemory);
void LCD_Show(Epd LCDMemory);
void LCD_Clear(Paint* LCDScreen, int colored);
void LCD_ClearAll(Epd LCDMemory);


void LCD_TestModeWithButton(Paint* LCDScreen, Epd* LCDMemory);

///////// Application


/* FILE END */


#endif
