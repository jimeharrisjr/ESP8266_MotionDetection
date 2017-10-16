# ESP8266_MotionDetection
A project using the ESP8266 and motion sensor with the Arduino IDE and [IFTTT.com](https://ifttt.com/discover) for home security.

I use this with IFTTT (If This Than That) webhooks to output into [Slack](https://slack.com/), which is then connected to my Raspberry Pi 
Listening to Slack (and waiting for this trigger to take a picture from its camera and upload it into Slack. It's a very inexpensive
"Security System." However, you can use the motion detector independently, if you wish. IFTTT makes it possible for you to do virtually
anything from this one simple stimulus.

## Prerequisites
This is a hardware and software project using very inexpensive hardware you can find widely available. 
### Hardware
At the core of the project
is an ESP8266 WiFi module, which can be found for $2-$6 online (the exact ones used in this project can be found [here](https://www.amazon.com/gp/product/B01N0XQM0Q/ref=oh_aui_search_detailpage?ie=UTF8&psc=1).

The other major component is the motion sensor. I used the [VMA314](https://www.velleman.eu/products/view/?id=435542) from Velleman, which I picked up from Micro Center.

This project needs both 5V (for the detector) and 3.3V for the ESP8266. Although there are a lot of ways to solve this problem, I used [this board](https://www.amazon.com/gp/product/B01ELAGIO6/ref=oh_aui_search_detailpage?ie=UTF8&psc=1) to make mine work in a breadboard-friendly way. It allows you to easily provide both 5V and 3.3V on different sides of the breadboard, uses USB as the power source (although it has exactly the WRONG connector for this purpose - but I have lots of USB adapters), and has a power button to boost. 

Finally, I needed two 2.2k Ohm resistors and a standard N-P-N transistor, which you can find in any hobby electronics store.

Optionally, you may want to use a breadboard, in which case I highly recommend using a breakout board for the very breadboard-unfriendly ESP module. The breakout board I used was [this one](https://www.amazon.com/gp/product/B01G6HK3KW/ref=oh_aui_detailpage_o09_s00?ie=UTF8&psc=1).

The build instructions for the hardware are in the [Hardware directory](Hardware), including a [circuit diagram](Hardware/circuit).

Obviously, you will need some way to program the ESP8266. Depending on your setup, there are many ways to do this (I've done it at least three ways so far), but here's a good way to get started at [DIY Hacking](https://diyhacking.com/esp8266-tutorial/).

### Software
You must have install the current upstream Arduino IDE at the 1.8 level or later. The current version is at the [Arduino Website](https://www.arduino.cc/en/main/software).

You will need to install the ESP8266 Ardino Core Library which you can find [here](https://github.com/esp8266/Arduino).

Clone this repository into the Arduino directory. You will need to configure the software for your particular install by altering the cred.h file with your WiFi userID and password:

```
// Define the ssid and password
extern const char* ssid = "<YOUR WIFI SSID>";
extern const char* password = "<YOUR WIFI PASSWORD>";
```
Then alter this section with the unique parameters for your IFTTT webhooks maker applet:
```
// Your event (below) may be customized as 'motion_in_Hall, etc.
extern const char* event="motion_detected";
extern const char* key="<YOUR IFTTT MAKER KEY>";
```

For more on how to create Webhooks Maker applets, please visit [IFTTT.com](https://ifttt.com/maker_webhooks).

Now, upload your Sketch to the ESP8266 and enjoy! When turned on, your IFTTT webhook maker should trigger with each movement.




