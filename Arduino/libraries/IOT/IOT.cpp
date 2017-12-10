#define VERSION "0.0.1"

#include "IOT.h"



IOT::IOT()
{
	//debugging
	Serial.begin(115200);
	Serial.println("");
	Serial.println("Booting");
}

void IOT::setup(String hostName){
	
	//Wi-Fi
  	WiFiManager wifiManager;
//temp
  	//wifiManager.resetSettings();
	
	wifiManager.setConfigPortalTimeout(180);
	
	wifiManager.autoConnect();
	
	
	//remote debugging
	Debug.begin(hostName);
  	Debug.setResetCmdEnabled(true);
  	Debug.setSerialEnabled(true);

	//OTA
	setupOTA();
}

void IOT::startLoop(){
	ArduinoOTA.handle();	
}

void IOT::endLoop(){
	Debug.handle();
}

void IOT::setupOTA(){
	ArduinoOTA.setPassword((const char *)"123");
	ArduinoOTA.onStart([&]() {
		Debug.println("Start");
	});
	ArduinoOTA.onEnd([&]() {
		Debug.println("\nEnd");
	});
	ArduinoOTA.onProgress([&](unsigned int progress, unsigned int total) {
		Debug.printf("Progress: %u%%\r", (progress / (total / 100)));
	});
	ArduinoOTA.onError([&](ota_error_t error) {
		Debug.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) Debug.println("Auth Failed");
		else if (error == OTA_BEGIN_ERROR) Debug.println("Begin Failed");
		else if (error == OTA_CONNECT_ERROR) Debug.println("Connect Failed");
		else if (error == OTA_RECEIVE_ERROR) Debug.println("Receive Failed");
		else if (error == OTA_END_ERROR) Debug.println("End Failed");
	});
	ArduinoOTA.begin();
}


