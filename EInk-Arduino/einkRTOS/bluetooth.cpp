#include "lib.h"

String BluetoothRcvString = "";  
String BluetoothSendString = ""; 
int sendSTATUS = 0;
int startTIME;

void BluetoothInit()
{
  BluetoothSerial.begin(BluetoothBaudRate);
  pinMode(HC05_KEY, OUTPUT);
  digitalWrite(HC05_KEY, LOW); 
  BluetoothReset();
}

// MODE=1: Command Mode
// MODE=0: Auto Mode
void BluetoothModeSwitch(int MODE)
{
  int HC05_KEY_state = digitalRead(HC05_KEY);

  if(HC05_KEY_state==0) // Being in Auto mode
  {
    if(MODE==1)
      digitalWrite(HC05_KEY, HIGH); 
  }
  else
  {
    if(MODE==0)
      digitalWrite(HC05_KEY, LOW); 
  }
  
  BluetoothReset();
}

void BluetoothReset()
{
  BluetoothSerial.println("AT+RESET");
}

void BluetoothSearch()
{
  BluetoothSerial.println("AT+INIT");
  BluetoothSerial.println("AT+ROLE=1");
  BluetoothSerial.println("AT+CMODE=1");
  BluetoothSerial.println("AT+INQ");

  int i;
  char inChar;

  for(i=0;i<10;i++)
  {
    inChar = (char)BluetoothSerial.read();
    if(inChar !=-1)
    {
      Serial.println(inChar);
    }
  }
}




void TaskBluetooth(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    if(BluetoothSerial.available())
    {
      char inChar = (char)BluetoothSerial.read();

      if(inChar !=-1)
      {
        //Serial.println("HAHA");
        if(sendSTATUS==0)
        {
          startTIME   = millis();  
          sendSTATUS  = 1;
        }
       
        BluetoothRcvString += inChar;
      }

      if(sendSTATUS==1 && (startTIME-millis()>=500))
      {
        sendSTATUS = 0;
        if(DEBUG_MODE)
            Serial.print("(TaskBluetooth): ");
        Serial.println(BluetoothRcvString);
        BluetoothRcvString="";
      }
    }

    vTaskDelay( 10 / portTICK_PERIOD_MS ); // wait for 10ms
  }
}

//void serialEvent() {
//  while(BluetoothSerial.available())
//  {
//      // get the new byte:
//      char inChar = (char)BluetoothSerial.read();
//      // add it to the inputString:
//
//      if(inChar !=-1)
//      {
//        if(sendSTATUS==0)
//        {
//          startTIME   = millis();  
//          sendSTATUS  = 1;
//        }
//        
//        inputString += inChar;
//      }
//
//      if(sendSTATUS==1 && (startTIME-millis()>=500))
//      {
//        sendSTATUS = 0;
//        Serial.println(inputString);
//        inputString="";
//      }
//      
//      // if the incoming character is a newline, set a flag so the main loop can
//      // do something about it:
////      if (inChar == '\n') {
////        
////      }
//  }  
//}

