/**
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


#include <SPI.h>
#include <epd1in54.h>
#include <epdif.h>
#include "imagedata.h"
#include "LCD_funcs.h"
#include "LCD_Chat_funcs.h"
#include "BtnScan.h"

/**
  * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
  * In this case, a smaller image buffer is allocated and you have to 
  * update a partial display several times.
  * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
  */
unsigned char image[1024];
Paint LCDScreen(image, 0, 0);    // width should be the multiple of 8 
Epd LCDMemory;
EInk_Chat ec(&LCDScreen, &LCDMemory);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (LCDMemory.Init(lut_full_update) != 0) {
      Serial.print("e-Paper init failed");
      return;
  }
  
  LCD_LoadImage(&LCDMemory, gImage_Email);
  delay(500);

  //LCD_ClearAll(LCDMemory);
  //ec.drawPtr(50,50,COLORED);
  
  
}

void loop() {

  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
  
  ec.startChat();
  //delay(100);
}

