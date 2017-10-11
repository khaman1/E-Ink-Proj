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

#include "LCD_Messenger.h"
#include "imagedata.h"
#include "lib.h"

char buf[50];

LCD_Messenger::LCD_Messenger(Paint* LCDScreen, Epd* LCDMemory)
{
  this->LCDScreen = LCDScreen;
  this->LCDMemory = LCDMemory;
  
  this->CHAT_STATE = STATE0;

}

LCD_Messenger::~LCD_Messenger()
{

}

void LCD_Messenger::Init()
{
  if (this->LCDMemory->Init(lut_full_update) != 0) {
      Serial.print("e-Paper init failed");
      return;
  }
}

void LCD_Messenger::Intro()
{
  Init();
  LCD_ClearAll(*this->LCDMemory);
  LCD_LoadImage(this->LCDMemory, gImage_Email);
  delay(100);
}

void LCD_Messenger::Start()
{
  Paint *LCDScreen = this->LCDScreen;
  Epd *LCDMemory = this->LCDMemory;

  int option;
  char inChar;
  char customKey;
  String txt;
  

  switch(this->CHAT_STATE)
  {
    case STATE0:
      Intro();
      BluetoothInit();
      this->CHAT_STATE = STATE1;
      break;

    case STATE1:
      option = mainMenu();

      if(option == 1) // Connect
        this->CHAT_STATE = STATE2_1;
      else if(option == 2) // Setting
        this->CHAT_STATE = STATE2_2;

      break;

    case STATE2_1: // Connect
      LCD_SetArea(LCDScreen, 16, 120, 270);
      LCD_DrawString(LCDScreen, LCDMemory, 190, 75, "Connecting", 18, COLORED);
      LCD_Show(*LCDMemory);

      while((inChar = (char)BluetoothSerial.read()) == -1);

      txt = inChar + BluetoothRead();
      Serial.println(txt);
      txt.toCharArray(buf, sizeof(buf));
      
      // LCD_Show(*this->LCDMemory);

      

      

      // LCD_Show(*this->LCDMemory);

      // Actively connect to device

      this->CHAT_STATE = STATE5;
      break;

    case STATE2_2: // Setting
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


      break;

    case STATE5: // Chat
      LCD_ClearAll(*this->LCDMemory);
      this->posX = 45;
      this->posY = RIGHTY;
      this->TextX = 8;
      this->TextY = 180;
      this->Text = "";
      this->TextCnt = 0;
      
      this->MESSAGE_STATUS = 0;

      LCDScreen->SetWidth(1);
      LCDScreen->SetHeight(200);
      LCDScreen->Clear(UNCOLORED);
      LCDScreen->DrawLine(0, 1, 3, 500, COLORED);
      LCDMemory->SetFrameMemory(LCDScreen->GetImage(), 24, 0, LCDScreen->GetWidth(), LCDScreen->GetHeight());
      
      newLineChat(buf, LEFT_ALIGN, UNCOLORED);
      LCD_Show(*this->LCDMemory);

      

      while(1)
      {
        //newLineChat("Hello PC", RIGHT_ALIGN, COLORED);

        // newLineChat("Hello Kha", LEFT_ALIGN, UNCOLORED);

        // newLineChat("How are you?", RIGHT_ALIGN, COLORED);
        // newLineChat("I'm super great!", LEFT_ALIGN, UNCOLORED);

        // newLineChat("Wanna meet tonight?", RIGHT_ALIGN, COLORED);
        // newLineChat("Absolutely, man!", LEFT_ALIGN, UNCOLORED);
  
        // newLineChat("Where can I reach you?", RIGHT_ALIGN, COLORED);
        // newLineChat("Denver downtown", LEFT_ALIGN, UNCOLORED);

        // newLineChat("See you there. Bye!", RIGHT_ALIGN, COLORED);
        // newLineChat("Bye", LEFT_ALIGN, UNCOLORED);
        //LCD_Show(*this->LCDMemory);
        

        // while(1)
        // {
        insertTextwithPointer();
        if((inChar = (char)BluetoothSerial.read())!=-1)
        {
          LCD_Show(*this->LCDMemory);
          txt = inChar + BluetoothRead();
          txt.toCharArray(buf, sizeof(buf));
          newLineChat(buf, LEFT_ALIGN, UNCOLORED);
          LCD_Show(*this->LCDMemory);

        }
        // }
      }
      break;


    // case STATE2:
    //   //LCD_DrawString("Waiting for connection ...");
    //   LCD_SetArea(LCDScreen, 16, 190, 270);
    //   LCD_Clear(LCDScreen, UNCOLORED);
    //   LCD_DrawString(LCDScreen, LCDMemory, 190, 9, "Waiting for connection ...", 12, COLORED);
    //   LCD_Show(*LCDMemory);

    //   this->CHAT_STATE = STATE3;
    //   break;

    default:
      break;
  }
}

int LCD_Messenger::mainMenu()
{
  char customKey;
  int option=1;

  LCD_ClearAll(*this->LCDMemory);

  LCD_SetArea(LCDScreen, 24, 125, 270);
  LCD_DrawString(LCDScreen, LCDMemory, 60, 34, "CONNECT", 24, UNCOLORED); // BOLD
  LCD_DrawString(LCDScreen, LCDMemory, 120, 34, "SETTING", 24, COLORED);

  LCD_Show(*this->LCDMemory);

  while(1)
  {
    customKey = customKeypad.getKey();
    if(customKey=='2' || customKey=='4' || customKey=='6' || customKey=='8') // UP
    {
      if(option == 1)
      {
        option = 2;

        LCD_DrawString(LCDScreen, LCDMemory, 60, 34, "CONNECT", 24, COLORED); // BOLD
        LCD_DrawString(LCDScreen, LCDMemory, 120, 34, "SETTING", 24, UNCOLORED);
      }
      else if(option == 2)
      {
        option = 1;

        LCD_DrawString(LCDScreen, LCDMemory, 60, 34, "CONNECT", 24, UNCOLORED); // BOLD
        LCD_DrawString(LCDScreen, LCDMemory, 120, 34, "SETTING", 24, COLORED);
      }

      LCD_Show(*this->LCDMemory);
    }
    else if(customKey=='5')
    {
      return option;
    }
  }
}


void LCD_Messenger::newLineChat(const char* TEXT, int alignment, int colored)
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
  LCD_SetArea(this->LCDScreen, 12, RIGHTY+Length*7, 270);
  

  if(alignment == RIGHT_ALIGN)
    this->posY = RIGHTY;
  else
    this->posY = LEFTY-Length*7;
    
  LCD_DrawString(this->LCDScreen, this->LCDMemory, this->posX, this->posY, TEXT, 12 , colored);

  // Save the posY  as Y-axis of the current pointer
  if(alignment == RIGHT_ALIGN)
    this->posY +=  (Length+1)*7;
  else
    this->posY -= 12;
    


  // Draw the pointer
  drawPtr(this->posX, this->posY,COLORED);
  
  // Update the pointer
  if(this->posX>=LEFTY-20)
    this->posX = 45;
  else
  {
    if(!colored)
      this->posX += 16;
    else
      this->posX += 24;
  }
  

  
}

void LCD_Messenger::drawPtr(int x, int y, int FILLED)
{
  Paint *LCDScreen = this->LCDScreen;
  Epd *LCDMemory = this->LCDMemory;

  LCDScreen->SetHeight(8);
  LCDScreen->SetWidth(6);
  LCDScreen->Clear(FILLED);
  LCDMemory->SetFrameMemory(LCDScreen->GetImage(), x, y, LCDScreen->GetWidth(), LCDScreen->GetHeight());

}

void LCD_Messenger::CleanTheLine(int x)
{
  Paint *LCDScreen = this->LCDScreen;
  Epd *LCDMemory = this->LCDMemory;

  LCDScreen->SetHeight(200);
  LCDScreen->SetWidth(12);
  LCDScreen->Clear(UNCOLORED);
  LCDMemory->SetFrameMemory(LCDScreen->GetImage(), x, 0, LCDScreen->GetWidth(), LCDScreen->GetHeight());
}

void LCD_Messenger::insertTextwithPointer()
{
  Paint *LCDScreen = this->LCDScreen;
  Epd *LCDMemory = this->LCDMemory;

  char customKey;

  customKey = customKeypad.getKey();

  if(customKey)
  {
    if(customKey!='#')
    {
      LCD_Show(*LCDMemory);
      LCD_SetArea(LCDScreen, 12, 20, 270);
      LCDScreen->Clear(UNCOLORED);
      //LCD_DrawString(this->LCDScreen, this->LCDMemory, 10, 180, "1", 12, COLORED);
      LCDScreen->DrawCharAt(5,0,customKey,&Font12,COLORED);
      LCDMemory->SetFrameMemory(LCDScreen->GetImage(), this->TextX, this->TextY, LCDScreen->GetWidth(), LCDScreen->GetHeight());
      LCD_Show(*LCDMemory);


      // Update for the next position
      this->TextY -= 10;

      // Append to the text
      this->Text += customKey;

    }
    else // Send
    {
      LCD_Show(*this->LCDMemory);
      // Send the message via Bluetooth
      this->Text.toCharArray(buf, sizeof(buf));
      BluetoothSend(buf,0);

      // Display a new line chat
      newLineChat(buf, RIGHT_ALIGN, COLORED);
      
      // Reset position
      this->TextX = 8;
      this->TextY = 180;
      this->Text  = "";
      this->TextCnt = 0;

      // Clear the text line
      CleanTheLine(8);


      // Show
      LCD_Show(*this->LCDMemory);
    }
  }
}


int LCD_Messenger::searchDevices(int option)
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
      else if(customKey=='*')
      {
        this->CHAT_STATE=STATE1;
        return -2;
      }

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