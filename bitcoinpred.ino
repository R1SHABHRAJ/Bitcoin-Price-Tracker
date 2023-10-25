
#include <SPI.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h> 
#include <WiFi.h>        // Include the Wi-Fi library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
 
const char* ssid     = "yourssid";                    //replace with your SSID
const char* password = "yourpassword";                         //replace with your PW
 
// API server
const char* host = "api.coindesk.com";
int key = 0;

void setup() {
   // Serial
  Serial.begin(115200);
  delay(10);
   // Initialize display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  display.clearDisplay();
  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(8,0);
  display.println("Bit Ticker");
  //display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(5,16);
  display.println("Bitcoin Price Teller"); 
  display.display();
  delay(1500);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.println("Project by:"); 
  display.println("Your Name");
  display.println("Your designation");
  display.display();
  delay(1500);
  display.clearDisplay();

 
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    display.setTextSize(1);
    display.setCursor(0,0);
    display.setTextColor(WHITE);
    display.println("Connecting to");
    display.println("wifi");
    display.println(ssid);
    display.clearDisplay();
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  display.println("WiFi connected");
  display.println(WiFi.localIP());
  display.clearDisplay();
  delay(200);

}
 
void loop() { 
// Connect to API
  Serial.print("connecting to ");
  Serial.println(host);
  
// Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
// We now create a URI for the request
  String url = "/v1/bpi/currentprice.json";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
// This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(100);
  
// Read all the lines of the reply from server and print them to Serial
  String answer;
  while(client.available()){
    String line = client.readStringUntil('\r');
    answer += line;
  }
 
  client.stop();
  Serial.println();
  Serial.println("closing connection");
  Serial.println();
  Serial.println("Answer: ");
  Serial.println(answer);
 
  String jsonAnswer;
  int jsonIndex;
 
  for (int i = 0; i < answer.length(); i++) {
    if (answer[i] == '{') {
      jsonIndex = i;
      break;
    }
  }
 
  jsonAnswer = answer.substring(jsonIndex);
  Serial.println();
  Serial.println("JSON answer: ");
  Serial.println(jsonAnswer);
  jsonAnswer.trim();
 
  int rateIndex = jsonAnswer.indexOf("rate_float");
  String priceString = jsonAnswer.substring(rateIndex + 12, rateIndex + 18);
  priceString.trim();
  float price = priceString.toFloat();
  int Price = round(price);
  if (Price != 0)
    {
     key = Price;
    }
  else
  {
    Serial.println('Update not available');
  }   
   // Print price
  Serial.println();
  Serial.println("Bitcoin price: ");
  Serial.println(key);
  // Display on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(25,0);
  display.print("Bitcoin Price");
  display.setTextSize(3);
  display.setCursor(20,10);
  display.println(key);
  display.display();
 // Wait 5 seconds
  delay(5000);
}