#include "lib.h"
#include "LCD_funcs.h"
#include "imagedata.h"

unsigned char image[1024];
Paint LCDScreen(image, 0, 0);    // width should be the multiple of 8 
Epd LCDMemory;
EInk_Chat ec(&LCDScreen, &LCDMemory);


void lcdIntro()
{
    if (LCDMemory.Init(lut_full_update) != 0) {
        Serial.print("e-Paper init failed");
        return;
    }

    LCD_LoadImage(&LCDMemory, gImage_Email);
    delay(500);
}

void TaskLCD(void *pvParameters)  // This is a task.
{
  char character;
  int i;
  
  for(;;)
  {
    // for(i=0;i<queueSize;i++)
    // {
    //     xQueueReceive(btnQueue, &character, portMAX_DELAY);
        
    // }
    ec.startChat();
  }
}
