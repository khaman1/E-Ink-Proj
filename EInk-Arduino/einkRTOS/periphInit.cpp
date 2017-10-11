#include "lib.h"

SemaphoreHandle_t xSerialSemaphore;
SemaphoreHandle_t xSerial2Semaphore;

void periphInit()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // initialize Bluetooth
  BluetoothInit();

  // LCD Intro
  lcdIntro();
  
  // initialize semaphore for Serial
  if ( xSerialSemaphore == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    if ( ( xSerialSemaphore ) != NULL )
      xSemaphoreGive( ( xSerialSemaphore ) );  // Make the Serial Port available for use, by "Giving" the Semaphore.
  }
  
  if ( xSerial2Semaphore == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerial2Semaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    if ( ( xSerial2Semaphore ) != NULL )
      xSemaphoreGive( ( xSerial2Semaphore ) );  // Make the Serial Port available for use, by "Giving" the Semaphore.
  }
  
  
  btnQueue = xQueueCreate( queueSize, sizeof( char ) );
  if(btnQueue == NULL){
    Serial.println("Error creating the queue");
  }
}