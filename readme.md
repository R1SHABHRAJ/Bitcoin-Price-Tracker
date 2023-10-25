# Bitcoin Price Ticker
This project is a Bitcoin price ticker that fetches the current price of Bitcoin from the CoinDesk API and displays it on an OLED display.

## Dependencies
The project uses the following libraries:

SPI.h
ArduinoJson.h
Wire.h
Adafruit_SSD1306.h
Adafruit_GFX.h
WiFi.h
## Hardware
The hardware required for this project is an ESP8266 or NodeMCU with an OLED display.

## Setup
Connect the OLED display with ESP8266 or NodeMCU board as shown in the schematic.
Replace the ssid and password variables in the code with your WiFi SSID and password.
Upload the code to your board.

## Usage
Once the code is uploaded and the Arduino board is powered on, it will connect to the specified WiFi network. It will then start fetching the current price of Bitcoin from the CoinDesk API every 5 seconds and display it on the OLED screen.