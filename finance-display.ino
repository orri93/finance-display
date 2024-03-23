#include <WiFi.h>
#include <HTTPClient.h>
#include <gatltick.h>

#include "types.h"
#include "constdef.h"
#include "secrets.h"
#include "display.h"
#include "queries.h"
#include "format.h"
#include "parse.h"
#include "rdd.h"

#define INTERVAL                  5000
#define DISPLAY_INTERVAL           500

#define SERIAL_BAUD_RATE          9600

#define BUFFER_SIZE               1024

::gos::atl::Tick<> tick(INTERVAL);
::gos::atl::Tick<> display_tick(DISPLAY_INTERVAL);

fd_rdd_data rdd_data;

char qb[BUFFER_SIZE];

const char* qp;
String payload;

size_t fs, dat;

unsigned long current;
int result;

void setup() {
  fs = 0;
  dat = 0;

  init_rdd_data(&rdd_data);

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
      qp = create_quotes_query();
      if (qp) {
#ifdef SERIAL_BAUD_RATE
        Serial.println(qp);
#endif
        http.begin(qp);
        result = http.GET();
        if (result > 0) {
          if (result == HTTP_CODE_OK) {
            payload = http.getString();
            parse_rdd_result(&rdd_data, payload);
#ifdef SERIAL_BAUD_RATE
            if (rdd_data.market_status.open) {
              Serial.println("Open");
            } else {
              Serial.println("Closed");
            }
            Serial.print("Quote Count: ");
            Serial.println(rdd_data.count);
            for (int i = 0; i < rdd_data.count; i++) {
              Serial.print("Price for ");
              Serial.print(rdd_data.quotes[i].symbol);
              Serial.print(": ");
              Serial.println(rdd_data.quotes[i].price);
            }
#endif
            fd_display_show_finance_status(&rdd_data);
            fs = fd_format_quotes(qb, &rdd_data);
            if (fs < dat) {
              dat = 0;
            }
#ifdef SERIAL_BAUD_RATE
            Serial.println(qb);
#endif
          }
        }
      }
    }

    if (display_tick.is(current)) {
      if (qb) {
        fd_display_show_quotes(qb, fs, dat);
        dat++;
        if (dat >= fs) {
          dat = 0;
        }
      } else {
        fd_display_show_empty_quotes();
      }
    }

  }
}
