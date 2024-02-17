#include <WiFi.h>
#include <HTTPClient.h>
#include <gatltick.h>

#include "constdef.h"
#include "display.h"
#include "secrets.h"

#define INTERVAL                  5000

#define SERIAL_BAUD_RATE          9600

::gos::atl::Tick<> tick(INTERVAL);

unsigned long current;

void setup() {

#ifdef SERIAL_BAUD_RATE
  Serial.begin(SERIAL_BAUD_RATE);
#endif

  fd_display_init();
  fd_display_show_status(STATUS_CONN_WIFI);

#ifdef SERIAL_BAUD_RATE
  Serial.println("Connecting WiFi");
#endif

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef SERIAL_BAUD_RATE
    Serial.print(".");
#endif
    fd_display_show_connection_progress();
  }
#ifdef SERIAL_BAUD_RATE
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
#endif
}

void loop() {
  current = millis();

  if (WiFi.status() == WL_CONNECTED) {
    if (tick.is(current)) {
      HTTPClient http;
    }
  }
}
