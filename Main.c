#include <WiFi.h>
#include <WiFiClientSecure.h>

//------- Replace using your Wireless information ------
char ssid[] = "WiFiName";          // your network SSID (name)
char password[] = "WiFiPassword";  // your network key (password)

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) { // Connect in your network 
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  delay(1000);
}
