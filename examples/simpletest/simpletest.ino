/*

 Simple Test
 
 */

//
// Note: The Arduino IDE does not respect conditional included
// header files in the main sketch so you have to select your
// hardware here, and in ModbusTCP.h.
//
// If you want to use both wired and wireless in different 
// projects copy ModbusTCP.h and ModbusTCP.cpp to the individual
// sketch folders instead of installing the library.
//

#include <Ethernet.h>
//#include <Adafruit_CC3000.h>

#include <SPI.h>
#include "ModbusTCP.h"

// Register map for this example
#define S1_FloatConstant 40001 // modpoll -m tcp -t 4:float -r 40001 [ip_addr] 
#define S1_CurrentMillis 40003 // modpoll -m tcp -t 4:int -r 40003 [ip_addr]
#define S1_FeetPerMile   40005 // modpoll -m tcp -t 4 -r 40005 [ip_addr]

ModbusTCP m;

void setup(void)
{
  Serial.begin(115200);
  
  // set some initial values
  m.setFloat(S1_FloatConstant, PI);
  m.setU32(S1_CurrentMillis, millis());
  m.setU16(S1_FeetPerMile, 5280);
  
  uint8_t mac[]     = { 0x70, 0xFF, 0x76, 0x00, 0xDF, 0x25 };
  m.begin(mac);
  //m.begin("myssid","mypass", WLAN_SEC_WPA2);
}

void loop(void)
{
  // Process MODBUS requests on every scan
  m.run();
  
  // Update the MODBUS registers  
  m.setU32(S1_CurrentMillis, millis());
}



