
#ifndef IOT_h
#define IOT_h

#include "Arduino.h" //Arduino constands, board definitions
#include "ArduinoOTA.h" //Over-the-air updates
#include "RemoteDebug.h" //remote debugging telnet server
#include "WiFiManager.h" //Wi-Fi Soft AP
#include <Ticker.h>  //interval for blinking LED during Wi-Fi configuration

class IOT
{
  public:
    IOT();
    void setup(String hostName);
    void startLoop();
    void endLoop();
    RemoteDebug Debug;
  private:
    void setupOTA();

    
};

#endif