#ifndef BLUETOOTHHC05_H
#define BLUETOOTHHC05_H

#include<Arduino.h>

#define BluetoothSerial Serial2
#define BluetoothBaudRate 38400
#define HC05_KEY 26

extern int STEP;

void BluetoothInit();
void BluetoothModeSwitch(int MODE);
void BluetoothReset();
void BluetoothSearch();

String AddrfixDelimiter(String Addr);
String BluetoothGetAddrName(String Addr);
void BluetoothLink(String Addr);


String BluetoothSend(const char* TXT, int wait_to_return);
void BluetoothSendSerial(char* TXT, int cnt);
String BluetoothRead();

#endif
