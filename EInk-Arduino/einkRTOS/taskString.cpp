#include "lib.h"


void TaskString(void *pvParameters)  // This is a task.
{
  char character;
  int i;
  
  for(;;)
  {
    for(i=0;i<queueSize;i++)
    {
        xQueueReceive(btnQueue, &character, portMAX_DELAY);
        
        if(DEBUG_MODE)
            if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
                {
                    Serial.print("(taskString): ");
                    Serial.println(character);
                    xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
                }
        
    }
    
    
    // if(btnString!="")
    // {
        
    // }
    
    //Serial.print("TaskString running... ");
    //Serial.println(btnString);
    vTaskDelay( 10 / portTICK_PERIOD_MS ); // wait for one second
  }
}