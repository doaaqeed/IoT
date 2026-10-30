#include <DHT.h>
#include "WiFi.h"
#include <ThingSpeak.h>

const char* WIFI_Name = "Wokwi-GUEST";
const char* WIFI_Pass = "";
const int channelID = 3559859;
const char* apiKey = "LQQDWNIMK4AGYWDL";

WiFiClient clientObject;
DHT senorDHT(15, DHT22);

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_Name, WIFI_Pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Status: Not Connected");
    delay(1000);
  }

  ThingSpeak.begin(clientObject);
  Serial.println("Studebt ID : 12324197");
  Serial.println("Status: Connected");
}

void loop() {
  float temperature = senorDHT.readTemperature();
  float humidity = senorDHT.readHumidity();

  Serial.print("Temperature: ");
  Serial.println(temperature);

  Serial.print("Humidity: ");
  Serial.println(humidity);

  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);

  int stat = ThingSpeak.writeFields(channelID, apiKey);

  if (stat == 200) {
    Serial.println("Data Sent to ThingSpeak");
  }

   delay(20000);  // every 20 seconds
}
