#include "lib.h"
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {A3, A4, A5, A6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A0, A1, A2}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
QueueHandle_t btnQueue;
int queueSize = 10;

void TaskButton(void *pvParameters)  // This is a task.
{
    //String *tmp = (String*)pvParameters;
    
    char customKey;
    
    for (;;) // A Task shall never return or exit.
    {
        customKey = customKeypad.getKey();
        if (customKey)
        {
            xQueueSend(btnQueue, &customKey, portMAX_DELAY);
            if(DEBUG_MODE)
            {
                if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
                {
                    Serial.print("(TaskButton): ");
                    Serial.println(customKey);
                    xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
                }
                
                
            }
                
        }
            
        vTaskDelay( 2 / portTICK_PERIOD_MS ); // wait for one second
    }
}