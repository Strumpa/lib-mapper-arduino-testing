#include <Arduino.h>

#include <WiFi.h>
#include <mapper_cpp.h>

#include <string>
#include <vector>
#include <algorithm>

using namespace mapper;

// For disabling power saving
#include "esp_wifi.h"

const char* ssid     = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

const int NUM_SIGNALS = 1;
const int SIG_SIZE = 6;

Device* dev;
std::vector<Signal> signals;

void setup() {
  Serial.begin(115200);

  // Begin WiFi before creating mapper device
  WiFi.begin(ssid, password);

  // Disable WiFi power save (huge latency improvements)
  esp_wifi_set_ps(WIFI_PS_NONE);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  dev = new Device("ESP32");
  for (int i = 0; i < NUM_SIGNALS; ++i) {
    std::ostringstream sigName;
    sigName << "test" << i;
    float min = 0.0f;
    float max = 5.0f;
    signals.push_back(dev->add_signal(Direction::OUTGOING, sigName.str(), SIG_SIZE,
                                      Type::FLOAT, "V", &min, &max));
  }
}

void loop() {
  dev->poll();
  for (int i = 0; i < NUM_SIGNALS; ++i) {
    std::vector <float> vec (SIG_SIZE);
    for (int j = 0; j < SIG_SIZE; ++j){
      vec.push_back(j);
    }
    signals[i].set_value(vec);
    #Serial.println("adding vec to signal");
  }
}
