#include <Arduino.h>

#include "constdef.h"
#include "display.h"
#include "pins.h"

//                          1234567890123456789012345678901234567890
#define EMPTY_DISPLAY_LINE "                                        "

LiquidCrystal lcd(LC_RS_PIN, LC_EN_PIN, LC_D4_PIN, LC_D5_PIN, LC_D6_PIN, LC_D7_PIN);

byte charu[] = { 0x00, 0x00, 0x04, 0x0E, 0x1F, 0x00, 0x00, 0x00 };
byte chard[] = { 0x00, 0x00, 0x00, 0x1F, 0x0E, 0x04, 0x00, 0x00 };

static char displaybuffer[41];

void fd_display_init() {
  displaybuffer[40] = '\0';
  lcd.begin(40, 2);
  lcd.createChar(1, charu);
  lcd.createChar(2, chard);
  lcd.clear();
}

void fd_display_show_status(int status) {
  lcd.clear();
  switch(status) {
  case STATUS_CONN_WIFI:
    lcd.print("Connecting WiFi");
    lcd.setCursor(0, 1);
    lcd.print(".");
    break;
  }
}

void fd_display_show_connection_progress() {
  lcd.print(".");
}

void fd_display_show_finance_status(fd_rdd_data* data) {
  lcd.setCursor(0, 1);
  if (data->market_status.open) {
    lcd.print("Market status: Open  ");
  } else {
    lcd.print("Market status: Closed");
  }
}

void fd_display_show_empty_quotes() {
  lcd.setCursor(0, 0);
  lcd.print(EMPTY_DISPLAY_LINE);
}

void fd_display_show_quotes(char* buffer, size_t fs, size_t at) {
  lcd.setCursor(0, 0);
  if (fs - at >= 40) {
    memcpy(displaybuffer, buffer + at, 40);
  } else {
    size_t l = fs - at;
    memcpy(displaybuffer, buffer + at, l);
    memcpy(displaybuffer + l, buffer, 40 - l);
  }
  lcd.print(displaybuffer);
}