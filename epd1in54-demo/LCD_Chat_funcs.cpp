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
#include "BluetoothHC05.h"
#include "imagedata.h"
#include <avr/pgmspace.h>
#include "BtnScan.h"

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
  String txt;
  char customKey;
  char inChar;
  int option;

  switch(this->CHAT_STATE)
  {
    case STATE0:   // LCD Intro
      BluetoothInit();
      LCD_ClearAll(*this->LCDMemory);
      LCD_LoadImage(this->LCDMemory, gImage_Email);
      delay(100);
      this->CHAT_STATE = STATE1;
      break;

    case STATE1: // Become slave or master
      LCD_ClearAll(*this->LCDMemory);

      LCD_SetArea(LCDScreen, 16, 130, 270);
      LCD_DrawString(LCDScreen, LCDMemory, 80, 33, "Become Slave", 16, UNCOLORED); // BOLD

      LCD_SetArea(LCDScreen, 16, 150, 270);
      LCD_DrawString(LCDScreen, LCDMemory, 110, 20, "Become Master", 16, COLORED);

      LCD_Show(*this->LCDMemory);

      MASTER_MODE = 0; // Slave
      // Show GUI
      while(1)
      {
        customKey = customKeypad.getKey();
        if(customKey=='2' || customKey=='4' || customKey=='6' || customKey=='8') // UP
        {
          if(MASTER_MODE==0)
          {
            MASTER_MODE = 1; // Master

            LCD_SetArea(LCDScreen, 16, 130, 270);
            LCD_Clear(LCDScreen, UNCOLORED);
            LCD_DrawString(LCDScreen, LCDMemory, 80, 33, "Become Slave", 16, COLORED);

            LCD_SetArea(LCDScreen, 16, 150, 270);
            LCD_Clear(LCDScreen, UNCOLORED);
            LCD_DrawString(LCDScreen, LCDMemory, 110, 20, "Become Master", 16, UNCOLORED);

            LCD_Show(*this->LCDMemory);
          }
          else if(MASTER_MODE==1)
          {
            MASTER_MODE = 0; // Slave

            LCD_SetArea(LCDScreen, 16, 130, 270);
            LCD_Clear(LCDScreen, UNCOLORED);
            LCD_DrawString(LCDScreen, LCDMemory, 80, 33, "Become Slave", 16, UNCOLORED);

            LCD_SetArea(LCDScreen, 16, 150, 270);
            LCD_Clear(LCDScreen, UNCOLORED);
            LCD_DrawString(LCDScreen, LCDMemory, 110, 20, "Become Master", 16, COLORED);

            LCD_Show(*this->LCDMemory);
          }
        }
        else if(customKey=='5') // CHOOSE
        {
          break;
        }
      }
      

      
      if(MASTER_MODE==0) // Slave
      {
        BluetoothModeSwitch(0);
        Serial.println("SLAVE MODE");
        this->CHAT_STATE = STATE3;
      }
      else if(MASTER_MODE==1) // Master
      {
        BluetoothModeSwitch(1);
        Serial.println("MASTER MODE");
        this->CHAT_STATE = STATE2;
      }  

      
      break;

    case STATE2: // Search Devices
      LCD_ClearAll(*this->LCDMemory);
      LCD_SetArea(LCDScreen, 16, 190, 270);
      LCD_DrawString(LCDScreen, LCDMemory, 0,  9, "BT Paired Devices", 16, COLORED);
    
      LCD_DrawString(LCDScreen, LCDMemory, 30, 9, "Samsung Galaxy S7 Edge", 12, UNCOLORED);
      LCD_DrawString(LCDScreen, LCDMemory, 45, 9, "D8C4:E9:762688", 12, COLORED);

      LCD_DrawString(LCDScreen, LCDMemory, 70, 9, "Device1", 12, COLORED);
      LCD_DrawString(LCDScreen, LCDMemory, 85, 9, "2013:5:20144", 12, COLORED);

      LCD_DrawString(LCDScreen, LCDMemory, 110, 9, "Device2", 12, COLORED);
      LCD_DrawString(LCDScreen, LCDMemory, 125, 9, "15:FF:F31F3A", 12, COLORED);



      LCD_DrawString(LCDScreen, LCDMemory, 145, 9, "Bluetooth Search", 16, COLORED);
      LCD_DrawString(LCDScreen, LCDMemory, 175, 9, "RF Search", 16, COLORED);

      LCD_Show(*this->LCDMemory);


      option = searchDevices(1);

      BluetoothSend("AT+INIT",0);
      if(option == 2)
        BluetoothLink("2013,5,20122");
      else if(option == 3)
        BluetoothLink("15,FF,F31F3A");

      //BluetoothSearch();


      // while(1)
      // {
      //   txt = BluetoothRead();
      //   Serial.println(txt);
      // }
      
      // LCD_DrawString(LCDScreen, LCDMemory, 50, 46, "Kha Man's device", 12, UNCOLORED);
      // LCD_DrawString(LCDScreen, LCDMemory, 65, 46, "00:11:22:33:44:55", 12, COLORED);

      // LCD_DrawString(LCDScreen, LCDMemory, 95, 46, "Kha Man's 2nd device", 12, COLORED);
      // LCD_DrawString(LCDScreen, LCDMemory, 110, 46, "00:22:44:66:66:88", 12, COLORED);

      

      //STEP++;
      //BluetoothSend("AT",1,1);
      //BluetoothSend("AT",1,1);
      //Serial.println(BluetoothSend("AT",1));
      //Serial.println(BluetoothSend("AT+INIT",1));

      // BluetoothSend("AT",0);
      // delay(100);
      // Serial.println(BTStringScan());

      // BluetoothSend("AT+ROLE=1",0);
      // delay(100);
      // Serial.println(BTStringScan());

      // BluetoothSend("AT+INQ",0);
      // delay(100);
      // Serial.println(BTStringScan());

      // Serial.println("FINISH");

      //STEP++;
      // txt = BluetoothSend("AT",1);
      // Serial.println(txt);

      //BluetoothSend("AT+ROLE=1",0,2);
      //Serial.println(txt);

      // BluetoothSerial.println("AT");
      // Serial.print("AT: ");
      // while((txt=BTStringScan())=="");
      // Serial.println(txt);

      // BluetoothSerial.println("AT+ROLE=1");
      // Serial.print("AT+ROLE=1: ");
      // while((txt=BTStringScan())=="");
      // Serial.println(txt);

      // BluetoothSerial.println("AT+CMODE=1");
      // while((txt=BTStringScan())=="");
      // Serial.println(txt);

      // BluetoothSerial.println("AT+INQ");
      // while((txt=BTStringScan())=="");
      // Serial.println(txt);

      
      // txt = BTStringScan();
      // if(txt!="")
      //   Serial.println(txt);
      // else
      // {
      //   BluetoothSerial.println("AT");
      //   delay(100);
      // }
      this->CHAT_STATE = STATE3;
      break;

    case STATE3: 
      LCD_ClearAll(*this->LCDMemory);
      ChatFrame("Kha's PC");
      LCDScreen->DrawLine(0,20,0,50,UNCOLORED);
      LCDMemory->SetFrameMemory(LCDScreen->GetImage(), 16, 60, LCDScreen->GetWidth(), LCDScreen->GetHeight());
      // Init posX posY
      this->posX = 45;
      this->posY = 3;
      
      this->MESSAGE_STATUS = 0;
      //this->TEXT = "HELLO PC";
      this->CHAT_STATE = STATE4;
      break;

    case STATE4:
      if(this->MESSAGE_STATUS == 0)
      {
        newLineChat("Hello PC", RIGHT_ALIGN, COLORED);

        newLineChat("Hello Kha", LEFT_ALIGN, UNCOLORED);

        newLineChat("How are you?", RIGHT_ALIGN, COLORED);
        newLineChat("I'm super great!", LEFT_ALIGN, UNCOLORED);

        newLineChat("Wanna meet tonight?", RIGHT_ALIGN, COLORED);
        newLineChat("Absolutely, man!", LEFT_ALIGN, UNCOLORED);
  
        newLineChat("Where can I reach you?", RIGHT_ALIGN, COLORED);
        newLineChat("Denver downtown", LEFT_ALIGN, UNCOLORED);

        newLineChat("See you there. Bye!", RIGHT_ALIGN, COLORED);
        newLineChat("Bye", LEFT_ALIGN, UNCOLORED);

        LCD_Show(*this->LCDMemory);

        delay(2000);

        //LCD_Show(*this->LCDMemory);

        //LCD_ClearAll(*this->LCDMemory);

        //ChatFrame("Kha's S7 Edge");
        //newLineChat("HELLO PC", RIGHT_ALIGN, COLORED);
        //newLineChat("Hello Kha", LEFT_ALIGN, UNCOLORED);
        
        //LCD_Show(*this->LCDMemory);
        this->MESSAGE_STATUS = 1;
      }
      break;
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

int EInk_Chat::searchDevices(int option)
{
	Paint *LCDScreen = this->LCDScreen;
	Epd *LCDMemory = this->LCDMemory;
  char customKey;
  int MIN=1;
  int MAX=5;

  while(1)
  {
    customKey = customKeypad.getKey();
    if(customKey)
    {
      if(customKey=='2' || customKey=='4')
      {
        if(option == MIN)
          option = MAX;
        else
          option--;
      }
      else if(customKey=='6' || customKey=='8')
      {
        if(option == MAX)
          option = MIN;
        else
          option++;
      }
      else if(customKey=='5')
        return option;

      Serial.println(option);

      LCD_Show(*this->LCDMemory);

      switch(option)
      {
        case 1:
          LCD_SetArea(LCDScreen, 16, 190, 270);
          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 175, 9, "RF Search", 16, COLORED);

          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 30, 9, "Samsung Galaxy S7 Edge", 12, UNCOLORED);

          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 70, 9, "Device1", 12, COLORED);
          break;

        case 2:
          LCD_SetArea(LCDScreen, 16, 190, 270);
          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 30, 9, "Samsung Galaxy S7 Edge", 12, COLORED);

          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 70, 9, "Device1", 12, UNCOLORED);

          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 110, 9, "Device2", 12, COLORED);
          break;

        case 3:
          LCD_SetArea(LCDScreen, 16, 190, 270);
          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 70, 9, "Device1", 12, COLORED);

          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 110, 9, "Device2", 12, UNCOLORED);

          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 145, 9, "Bluetooth Search", 16, COLORED);
          break;

        case 4:
          LCD_SetArea(LCDScreen, 16, 190, 270);
          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 110, 9, "Device2", 12, COLORED);

          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 145, 9, "Bluetooth Search", 16, UNCOLORED);

          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 175, 9, "RF Search", 16, COLORED);
          break;

        case 5:
          LCD_SetArea(LCDScreen, 16, 190, 270);
          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 145, 9, "Bluetooth Search", 16, COLORED);

          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 175, 9, "RF Search", 16, UNCOLORED);

          LCD_Clear(LCDScreen, UNCOLORED);
          LCD_DrawString(LCDScreen, LCDMemory, 30, 9, "Samsung Galaxy S7 Edge", 12, COLORED);
          break;

        default:
          break;

      }

      
      LCD_Show(*this->LCDMemory);
    }
  }

  return -1;
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