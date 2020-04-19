#include "InstagramStats.h"
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"
#include "images.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "JsonStreamingParser.h"

//------- Replace using your Wireless information ------
char ssid[] = "espn8266";       // your network SSID (name)
char password[] = "jjjjjjjj";  // your network key (password)
int counter = 1;
int counter2 = 1;

WiFiClientSecure client;
InstagramStats instaStats(client);

unsigned long delayBetweenChecks = 60; // mean time between api requests
unsigned long whenDueToCheck = 0;

//Inputs
String userName = "johwconst"; // replace using your instagram account @name_user
String follow;

SSD1306Wire  display(0x3c, 18, 19); // Define your display

void drawProgressBarDemo() { // Fake ProgressBar
  int progress = (counter / 5) % 100;
  display.drawProgressBar(0, 32, 120, 10, progress); 

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%");
}

void drawImageDemo() {
    display.drawXbm(30, 20, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits); // Display a WiFi Logo
}

void setup() {
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  Serial.begin(115200);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) { // Connect in your network 
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 0, "Conectando..");
    drawImageDemo();
    display.display();
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 0, "Conectado a");
  display.setFont(ArialMT_Plain_24);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, ssid);
  display.display();
  delay(1000);
}

void getInstagramStatsForUser() {
  Serial.println("Getting instagram user stats for " + userName );
  InstagramUserStats response = instaStats.getUserStats(userName);
  display.clear();
  Serial.println(response.followedByCount);
  follow = response.followedByCount;
  while(counter2 < 500){
    drawProgressBarDemo();
    counter++;
    counter2++;
    display.display();
    display.clear();
    }
  delay(500);
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 0, userName);
  display.setFont(ArialMT_Plain_24);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, follow);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 50, "Seguidores");
  display.display();
  Serial.println("Response:");
  Serial.print("Number of followers: ");
  
}

void loop() {
  unsigned long timeNow = millis();
  if ((timeNow > whenDueToCheck))  {
    getInstagramStatsForUser();
    whenDueToCheck = timeNow + delayBetweenChecks;
  }
}