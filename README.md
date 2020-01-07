# zaka-monitor
system of measuring temperatures and humidity from many places.
## Introduction
The system consist of two parts: 
* presentation of the measurement result - the web app described [here](https://github.com/FZynwala/zaka-monitor)
* hardware part: network of wireless sensors measuring temperature and humidity
## Technologies
The sensor is built of:
* ESP8266 -  a low-cost Wi-Fi microchip with full TCP/IP stack and microcontroller capability
* DS18b20 - digital thermometer
* DHT11 - digital temperature and humidity sensor
* breadboard 50x70mm
* housing - Kradex 154x85x43mm
### Electric power supply
The device is powered by 6 AA batteries or a mains adapter. 
* Supply voltage: 7 - 12 V 
* Power consumption:
  * At peak: 75mA
  * Deep sleep: 1,7uA
## Principle of operation
After turning on the power, sensor is connecting to WiFi (WiFi credentials are hardcoded). Then it performs the measurement and sends the results to the proper endpoint. Subsequently it switches to deep sleep mode for 5 minutes. The whole cycle repeats. Data is stored in MongoDB database. The results of measurement can be seen using special web application described [here](https://github.com/FZynwala/zaka-monitor).
