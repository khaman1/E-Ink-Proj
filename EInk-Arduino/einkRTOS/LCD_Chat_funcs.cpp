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
#include "LCD_Chat_funcs.h"
#include <avr/pgmspace.h>

EInk_Chat::EInk_Chat(Paint* LCDScreen, Epd* LCDMemory)
{
	this->LCDScreen = LCDScreen;
	this->LCDMemory = LCDMemory;

  this->CHAT_STATE = STATE0;
}

EInk_Chat::~EInk_Chat()
{

}

void EInk_Chat::startChat()
{
  switch(this->CHAT_STATE)
  {
    case STATE0:   // Clear the screen
      LCD_ClearAll(*this->LCDMemory);     
      BluetoothSearch(); // start the search by Bluetooth
      this->CHAT_STATE = STATE1_1;
      break;

    case STATE1_1: // Search for devices;
      searchDevices();
      break;
      

//    case STATE1_1: // Initialization for the chat
//      LCD_ClearAll(*this->LCDMemory);
//      ChatFrame("Kha's S7 Edge");
//
//      // Init posX posY
//      this->posX = 45;
//      this->posY = 3;
//      
//      this->MESSAGE_STATUS = 0;
//      //this->TEXT = "HELLO PC";
//      this->CHAT_STATE = STATE1_2;
//      break;
//
//    case STATE1_2:
//      if(this->MESSAGE_STATUS == 0)
//      {
//        newLineChat("Hello PC", RIGHT_ALIGN, COLORED);
//
//        newLineChat("Hello Kha", LEFT_ALIGN, UNCOLORED);
//
//        newLineChat("How are you?", RIGHT_ALIGN, COLORED);
//        newLineChat("I'm super great!", LEFT_ALIGN, UNCOLORED);
//
//        newLineChat("Wanna meet tonight?", RIGHT_ALIGN, COLORED);
//        newLineChat("Absolutely, man!", LEFT_ALIGN, UNCOLORED);
//  
//        newLineChat("Where can I reach you?", RIGHT_ALIGN, COLORED);
//        newLineChat("Denver downtown", LEFT_ALIGN, UNCOLORED);
//
//        newLineChat("See you there. Bye!", RIGHT_ALIGN, COLORED);
//        newLineChat("Bye", LEFT_ALIGN, UNCOLORED);
//
//        LCD_Show(*this->LCDMemory);
//
//        delay(2000);
//
//        //LCD_Show(*this->LCDMemory);
//
//        //LCD_ClearAll(*this->LCDMemory);
//
//        //ChatFrame("Kha's S7 Edge");
//        //newLineChat("HELLO PC", RIGHT_ALIGN, COLORED);
//        //newLineChat("Hello Kha", LEFT_ALIGN, UNCOLORED);
//        
//        //LCD_Show(*this->LCDMemory);
//        this->MESSAGE_STATUS = 1;
//      }
//      break;
    default:
      break;
  }
}

void EInk_Chat::newLineChat(const char* TEXT, int alignment, int colored)
{
  int Length = strlen(TEXT); 
 
  // Clear the previous pointer
  if(this->posX == 45)
    drawPtr(181, this->posY,UNCOLORED);
  else
  {
    if(!colored)
      drawPtr(this->posX-24, this->posY,UNCOLORED);
    else
      drawPtr(this->posX-16, this->posY,UNCOLORED);  
  }
  

  // Clean the line as blank
  CleanTheLine(this->posX);

  // Update coordination for the the new text;
  LCD_SetArea(this->LCDScreen, 12, 0+Length*7, 270);
  

  if(alignment == RIGHT_ALIGN)
    this->posY = 3;
  else
    this->posY = 200-Length*7;
    
  LCD_DrawString(this->LCDScreen, this->LCDMemory, this->posX, this->posY, TEXT, 12 , colored);

  // Save the posY  as Y-axis of the current pointer
  if(alignment == RIGHT_ALIGN)
    this->posY +=  (Length+1)*7;
  else
    this->posY -= 12;
    


  // Draw the pointer
  drawPtr(this->posX, this->posY,COLORED);
  
  // Update the pointer
  if(this->posX>=180)
    this->posX = 45;
  else
  {
    if(!colored)
      this->posX += 16;
    else
      this->posX += 24;
  }
  

  
}

void EInk_Chat::searchDevices()
{
	Paint *LCDScreen = this->LCDScreen;
	Epd *LCDMemory = this->LCDMemory;

  // Found 2 devices
  if(true)
  {
    LCD_SetArea(LCDScreen, 32, 150, 270);
    
    LCD_DrawString(LCDScreen, LCDMemory, 30, 46, "Searching for devices ...", 12, COLORED);
    
    LCD_DrawString(LCDScreen, LCDMemory, 50, 46, "Kha Man's device", 12, UNCOLORED);
    LCD_DrawString(LCDScreen, LCDMemory, 65, 46, "00:11:22:33:44:55", 12, COLORED);

    LCD_DrawString(LCDScreen, LCDMemory, 95, 46, "Kha Man's 2nd device", 12, COLORED);
    LCD_DrawString(LCDScreen, LCDMemory, 110, 46, "00:22:44:66:66:88", 12, COLORED);

    LCD_Show(*this->LCDMemory);
    delay(200);
    
  }
  

	
}

void EInk_Chat::ChatFrame(const char* personName)
{
  Paint *LCDScreen = this->LCDScreen;
  Epd *LCDMemory = this->LCDMemory;
  //////////////////////////////////////
  

  //////////////////////////////////////
  // Chat title
  LCD_SetArea(LCDScreen, 14, 90, 270);
  LCD_DrawString(LCDScreen, LCDMemory, 30, 110, "Chatting with ", 12, COLORED);
  LCD_DrawString(LCDScreen, LCDMemory, 30, 15, personName, 12, COLORED);
}

void EInk_Chat::drawButton(int x, int y, int size, const char* TEXT, int colored, int FILLED)
{
	Paint *LCDScreen = this->LCDScreen;
	Epd *LCDMemory = this->LCDMemory;
	int radius;

	switch(size)
	{
		case 0:		radius = 8;		break;
		case 1:		radius = 12;	break;
		case 2:		radius = 16;	break;
		case 3:		radius = 20;	break;
		case 4:		radius = 20;	break;
		default:	radius = 15;	break;
	}

	LCDScreen->SetHeight(120);
  LCDScreen->SetWidth(60);
	LCDScreen->Clear(UNCOLORED);
	LCDScreen->DrawButton(x,y,radius,TEXT,colored,0);
	LCDMemory->SetFrameMemory(LCDScreen->GetImage(), x, y, LCDScreen->GetWidth(), LCDScreen->GetHeight());
	LCDMemory->DisplayFrame();
  LCD_Show(*LCDMemory);
}


void EInk_Chat::drawPtr(int x, int y, int FILLED)
{
  Paint *LCDScreen = this->LCDScreen;
  Epd *LCDMemory = this->LCDMemory;

  LCDScreen->SetHeight(8);
  LCDScreen->SetWidth(6);
  LCDScreen->Clear(FILLED);
  LCDMemory->SetFrameMemory(LCDScreen->GetImage(), x, y, LCDScreen->GetWidth(), LCDScreen->GetHeight());

}

void EInk_Chat::CleanTheLine(int x)
{
  Paint *LCDScreen = this->LCDScreen;
  Epd *LCDMemory = this->LCDMemory;

  LCDScreen->SetHeight(200);
  LCDScreen->SetWidth(12);
  LCDScreen->Clear(UNCOLORED);
  LCDMemory->SetFrameMemory(LCDScreen->GetImage(), x, 0, LCDScreen->GetWidth(), LCDScreen->GetHeight());

}
