#ifndef BLUETOOTHHC05_H
#define BLUETOOTHHC05_H

#include<Arduino.h>

#define BluetoothSerial Serial2
#define BluetoothBaudRate 38400
#define HC05_KEY 26



void BluetoothInit();
void BluetoothModeSwitch(int MODE);
void BluetoothReset();

#endif
