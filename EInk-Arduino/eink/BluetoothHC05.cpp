#include "BluetoothHC05.h"



void BluetoothInit()
{
  BluetoothSerial.begin(BluetoothBaudRate);
  pinMode(HC05_KEY, OUTPUT);
  digitalWrite(HC05_KEY, LOW); 
  //BluetoothReset();
}

void BluetoothSearch()
{
  // Serial.println(BluetoothSend("AT",1)); delay(100);
  // Serial.println(BluetoothSend("AT",1)); delay(100);
  // Serial.println(BluetoothSend("AT",1)); delay(100);
  // Serial.println(BluetoothSend("AT",1)); delay(100);
  // Serial.println(BluetoothSend("AT",1)); delay(100);
  // Serial.println(BluetoothSend("AT",1)); delay(100);
  //Serial.println(BluetoothSend("AT+INIT",1));
  // Serial.println(BluetoothSend("AT+CLASS=0",1));
  // Serial.println(BluetoothSend("AT+ROLE=1",1));
  // Serial.println(BluetoothSend("AT+CMODE=1",1));
  
  // String Device1 = BluetoothSend("AT+INQ",1);
  // Serial.println(Device1);
  // Device1 = AddrfixDelimiter(Device1);
  // Serial.println(Device1);

  // Serial.println(BluetoothGetAddrName(Device1));
}

// MODE=1: Command Mode
// MODE=0: Auto Mode
void BluetoothModeSwitch(int MODE)
{
  digitalWrite(HC05_KEY, MODE);
  BluetoothReset();
}


void BluetoothLink(String Addr)
{
  String text = "AT+LINK=" + Addr;

  char buf[50];
  text.toCharArray(buf, sizeof(buf));


  BluetoothSend(buf, 0);
}


String BluetoothGetAddrName(String Addr)
{
  String text = "AT+NAME? " + Addr;
  char buf[50];
  text.toCharArray(buf, sizeof(buf));


  String result = BluetoothSend(buf, 1);

  if(result == "ERROR: (0)" || result == "ERROR: (7)")
    return "Unknown Device";

  return result;
}







void BluetoothReset()
{
  BluetoothSerial.println("AT+RESET");
}

// wait_to_return=1: polling until receving the data back
// wait_to_return=0: no need
String BluetoothSend(const char* TXT, int wait_to_return)
{
  // String a = TXT;
  // a += "\r\n";

  BluetoothSerial.print(TXT); // Send 
  if(wait_to_return)    
    return BluetoothRead(); // Wait to receive

  return "";
}

void BluetoothSendSerial(char* TXT, int cnt)
{
  int i;
  for(i=0;i<cnt;i++)
    BluetoothSerial.print(TXT[cnt]);
}


String BluetoothRead()
{
  String BluetoothRevString = "";
  char inChar;
  while(1)
  {
    inChar = (char)BluetoothSerial.read();
    if (inChar == '\n')
      return BluetoothRevString;
    else if(inChar != -1)
      BluetoothRevString += inChar;
  }
}

String AddrfixDelimiter(String Addr)
{
  char buf[50];
  Addr.toCharArray(buf, sizeof(buf));
  char *p = buf;
  char *str;
  String result="";

  p = strtok_r(p, ",", &p);
  //Serial.println(p);

  // Throw away "+INQ"
  str = strtok_r(p, ":", &p);
  //Serial.println(str);

  // 1st part
  str = strtok_r(p, ":", &p);
  Serial.println(str);
  result = str;
  result += ',';

  // 2nd part
  str = strtok_r(p, ":", &p);
  Serial.println(str);
  result += str;
  result += ',';

  // 3rd part
  str = strtok_r(p, ":", &p);
  Serial.println(str);
  result += str;

  return result;
}


// String BluetoothRevString="";
// bool BTRevStringComplete = false;

// void serialEvent2() 
// {
//   while (1) {
//     // get the new byte:
//     char inChar = (char)BluetoothSerial.read();
//     // add it to the inputString:
//     // if the incoming character is a newline, set a flag so the main loop can
//     // do something about it:
    
//     if (inChar == '\n')
//     {
//       BTRevStringComplete = true;
//       break;
//     }
//     else
//       BluetoothRevString += inChar;
//   }
// }

// String BTStringScan()
// {
  
//   if(BTRevStringComplete)
//   {
//     BTRevStringComplete = false;
//     String txt = BluetoothRevString;
//     BluetoothRevString  = "";
//     return txt;
//   }

//   return "";
// }