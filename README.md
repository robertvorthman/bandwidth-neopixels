# bandwidth-neopixels
The node script continuously polls a [Tomato router](http://tomato.groov.pl/?page_id=81) for real-time bandwidth, then provides JSON to an Arduino or ESP8266 to visualize bandwidth on a strip of neopixels.

![animated gif](https://user-images.githubusercontent.com/4665046/33800605-3eac09fc-dd11-11e7-9417-000576d7396c.gif)

The pixels animate as a downward flow to show download speed or up when upload speed is larger.  Both download and upload are not visualized simultaneously, only the largest of the two values is shown.  The Arduino script uses the excellent [WS2812FX](https://github.com/kitesurfer1404/WS2812FX) library to create the neopixel animations.

[YouTube Video](https://www.youtube.com/watch?v=Yf8KJNKBrkc)

![fritzing diagram](https://user-images.githubusercontent.com/4665046/33800604-3ea3cfc6-dd11-11e7-82c8-b2089204d564.png)

![photograph of wemos d1 mini breadboard](https://user-images.githubusercontent.com/4665046/33800606-3eb444a0-dd11-11e7-82f3-2e966e24a722.jpg)

**REQUIRES A ROUTER RUNNING TOMATO FIRMWARE** or a router that has an API for real-time bandwidth.
