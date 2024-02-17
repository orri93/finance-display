#include <LiquidCrystal.h>

#include "constdef.h"
#include "display.h"
#include "pins.h"

static LiquidCrystal lcd(LC_RS_PIN, LC_EN_PIN, LC_D4_PIN, LC_D5_PIN, LC_D6_PIN, LC_D7_PIN);

void fd_display_init() {
  lcd.begin(20, 2);
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
