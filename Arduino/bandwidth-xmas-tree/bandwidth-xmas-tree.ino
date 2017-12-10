#include <IOT.h>
#include <WS2812FX.h>
#include <elapsedMillis.h>
#include <ArduinoJson.h>

#define LED_COUNT 450
#define LED_PIN D5

IOT iot;
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
WiFiClient client;

const char* remoteServer = "livingroom-pi";
const int remoteServerPort = 81;

//megabits per second to fill pixels to the top of the tree
int bandwidthMax = 150;

String text;
boolean startJson = false;
boolean endJson = false;

elapsedMillis sinceUpdate = 0;
int updateInterval = 1000;

void setup() {
  iot.setup("christmas-tree");
  text.reserve(40);

  ws2812fx.init();
  ws2812fx.setSegment(0, 0, LED_COUNT-1, FX_MODE_TWINKLE_FADE, (const uint32_t[]) {0x00ff00}, 1000, false);
  ws2812fx.start();
}

void loop() {
  iot.startLoop();
  handleBandwidthResponse();
  ws2812fx.service();
  iot.endLoop();
}

void handleBandwidthResponse(){
  char c = 0;
  if (client.available()) {
    c = client.read();
    
    if (c == '{') {
      startJson = true;
    }else if(c == '}') {
      endJson = true;
    }

    if (startJson) {
      text += c;
    }
    
    if (startJson && endJson) {
      parseJson(text.c_str());  // parse c string text in parseJson function
      startJson = false;
    } 

  }else{
    if(sinceUpdate > updateInterval){
      sinceUpdate = 0;
      getUpdate();
    }
  }
}

void parseJson(const char * jsonString) {
  StaticJsonBuffer<400> jsonBuffer;

  JsonObject& root = jsonBuffer.parseObject(jsonString);
  if (!root.success()) {
    iot.Debug.println("parseObject() failed");
    return;
  }

  float down = root["down"];
  float up = root["up"];

  iot.Debug.print(down);
  iot.Debug.print("/");
  iot.Debug.println(up);

  updateLights(down, up);
}

void getUpdate(){
  text = "";
  startJson = false;
  endJson = false;
  client.stop();
  if (client.connect(remoteServer, remoteServerPort)) {
    client.print(String("GET ") + "/ HTTP/1.1\r\n" +
      "Host: "+remoteServer+"\r\n" + 
      "Connection: close\r\n\r\n");
  }
}

void updateLights(float down, float up){
  float metric = down;
  boolean reverse = true;
  if(up>down){
    metric = up;
    reverse = false;
  }

  int pixel = map(metric, 0, bandwidthMax, 0, LED_COUNT - 1);
  pixel = constrain(pixel, 0, LED_COUNT - 1);
  int speed = map(metric, 0, bandwidthMax, 10, 40000);
  
  ws2812fx.setSegment(0, 0, pixel, FX_MODE_RUNNING_LIGHTS, (const uint32_t[]) {0xff0000}, speed, reverse);
  if(pixel < LED_COUNT - 1){
      ws2812fx.setSegment(1, pixel+1, LED_COUNT - 1, FX_MODE_TWINKLE_FADE, (const uint32_t[]) {0x00ff00}, 1000, false);
  }
}
