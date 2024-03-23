#ifndef _FINANCE_DISPLAY_H_
#define _FINANCE_DISPLAY_H_

#include <LiquidCrystal.h>
#include "types.h"

extern LiquidCrystal lcd;

void fd_display_init();
void fd_display_show_status(int status);
void fd_display_show_connection_progress();
void fd_display_show_finance_status(fd_rdd_data* data);
void fd_display_show_empty_quotes();
void fd_display_show_quotes(char* buffer, size_t fs, size_t at);
//void fd_display_update_

#endif /* _FINANCE_DISPLAY_H_ */
