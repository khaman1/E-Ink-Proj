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
#ifndef LCD_MESSENGER_H
#define LCD_MESSENGER_H

#include <epd1in54.h>
#include <epdpaint.h>
#include <fonts.h>
#include "LCD_funcs.h"

#define STATE0            0
#define STATE1            1
#define STATE2_1          2
#define STATE2_2          3
#define STATE3			  4
#define STATE4            5
#define STATE5			  6


#define STATE10			  10

#define LEFT_ALIGN        0
#define RIGHT_ALIGN       1
#define TOPX			  45
#define RIGHTY			  4
#define LEFTY			  200			


extern int MASTER_MODE;


class LCD_Messenger
{
	private:
		Paint *LCDScreen;
		Epd *LCDMemory;
		int posX;
	    int posY;
	    int MESSAGE_STATUS;
	    
	    String Text;
	    int TextCnt;

	    int TextX;
	    int TextY;
	    int CHAT_STATE;

	public:
		LCD_Messenger(Paint* LCDScreen, Epd* LCDMemory);
		~LCD_Messenger();

        void Init();
		void Intro();
        void Start();
        int mainMenu();
        void newLineChat(const char* TEXT, int alignment, int colored);
        void drawPtr(int x, int y, int FILLED);
        void CleanTheLine(int x);
        void insertTextwithPointer();
        int searchDevices(int option);

};






/* FILE END */


#endif
