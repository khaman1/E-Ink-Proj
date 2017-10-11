#ifndef _LIB_H
#define _LIB_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <epd1in54.h>
#include <epdif.h>
#include <epdpaint.h>
#include <fonts.h>
#include "LCD_funcs.h"
#include "LCD_Chat_funcs.h"
// 
#define DEBUG_MODE 1



// Global Variables
extern SemaphoreHandle_t xSerialSemaphore;
extern SemaphoreHandle_t xSerial2Semaphore;
extern QueueHandle_t btnQueue;
extern int queueSize;

extern String BluetoothRcvString;
extern String BluetoothSendString;

// Functions
void periphInit();
void taskInit();




/// TASKS
void TaskBlink(void *pvParameters);
void TaskButton(void *pvParameters);
void TaskLCD(void *pvParameters);
void TaskBluetooth(void *pvParameters);
// LOCAL

// Bluetooth
#define BluetoothSerial Serial2
#define BluetoothBaudRate 38400
#define HC05_KEY 26
void BluetoothInit();
void BluetoothReset();


// LCD
extern Paint LCDScreen;
extern Epd LCDMemory;
extern EInk_Chat ec;

void lcdIntro();

#endif
