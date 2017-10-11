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
#ifndef LCD_CHAT_FUNCS_H
#define LCD_CHAT_FUNCS_H

#include <epd1in54.h>
#include <epdpaint.h>
#include <fonts.h>

#define STATE0            0
#define STATE1            1
#define STATE2            2
#define STATE3            3
#define STATE4            4
#define STATE5            5
#define STATE10			  9

#define LEFT_ALIGN        0
#define RIGHT_ALIGN       1


extern int MASTER_MODE;


class EInk_Chat
{
	private:
		Paint *LCDScreen;
		Epd *LCDMemory;
		int posX;
	    int posY;
	    int MESSAGE_STATUS;
	    char* TEXT;
	    int CHAT_STATE;

	public:
		EInk_Chat(Paint* LCDScreen, Epd* LCDMemory);
		~EInk_Chat();

		int searchDevices(int option); 
	    void startChat();
	    void ChatFrame(const char* personName);
	    void newLineChat(const char* TEXT, int alignment, int colored);
		void drawButton(int x, int y, int size, const char* TEXT, int colored, int FILLED);
		void drawPointerArrow(int x, int y);  
		void drawPtr(int x, int y, int FILLED);
		void CleanTheLine(int x);
};






/* FILE END */


#endif
