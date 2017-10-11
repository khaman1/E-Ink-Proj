/**
 *  @filename   :   imagedata.cpp
 *  @brief      :   data file for epd demo
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

#include "LCD_funcs.h"
#include <avr/pgmspace.h>


void LCD_SetArea(Paint* LCDScreen, int Xpos, int Ypos, int ROTATION_DEGREE)
{
	int rotation;

	LCDScreen->SetWidth(Xpos);           	// Set the width of the area reserved for the show
  	LCDScreen->SetHeight(Ypos);         	// Set the heigh of the area reserved for the show
  	
  	switch(ROTATION_DEGREE)
  	{
  		case 0: 		rotation = ROTATE_0; 	break;
  		case 90:		rotation = ROTATE_90; 	break;
  		case 180:		rotation = ROTATE_180; 	break;
  		case 270:		rotation = ROTATE_270; 	break;
  		default: 		rotation = ROTATE_0;
  	}
  	LCDScreen->SetRotate(rotation);  		// Set the rotation of the display
}

void LCD_DrawString(Paint* LCDScreen, Epd* LCDMemory, int x, int y, const char* STRING, int FontSize, int colored)
{
  int TIMES;
  
  
  LCDScreen->Clear(!colored);
  
  // Retrieve the appropriate font array matched to Fontsize
  sFONT font;
  switch(FontSize)
  {
  	case 8:			font = Font8	; 		break;
  	case 12:		font = Font12	; 		break;
  	case 16:		font = Font16	; 		break;
  	case 20:		font = Font20	; 		break;
  	case 24:		font = Font24	; 		break;
  	default: 		font = Font16	;
  }

  
  LCDScreen->DrawStringAt(0, 0, STRING, &font, colored);
  LCDMemory->SetFrameMemory(LCDScreen->GetImage(), x, y, LCDScreen->GetWidth(), LCDScreen->GetHeight());
}

void LCD_LoadImage(Epd* LCDMemory, const unsigned char* image_buffer)
{
	LCDMemory->SetFrameMemory(image_buffer);
  LCDMemory->DisplayFrame();
}

bool LCD_Test(Epd LCDMemory)
{
	if (LCDMemory.Init(lut_partial_update) != 0) 
	{
      	Serial.print("e-Paper init failed");
      	return 0;
  	}

  	return 1;
}

void LCD_Show(Epd LCDMemory)
{
	LCDMemory.DisplayFrame();
}

void LCD_Clear(Paint* LCDScreen, int colored)
{
	LCDScreen->Clear(colored);
}

void LCD_ClearAll(Epd LCDMemory)
{
	LCDMemory.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  LCDMemory.DisplayFrame();
  LCDMemory.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  LCDMemory.DisplayFrame();
}




void LCD_TestModeWithButton(Paint* LCDScreen, Epd* LCDMemory);
