#ifndef _FINANCE_DISPLAY_FORMAT_H_
#define _FINANCE_DISPLAY_FORMAT_H_

#include <Arduino.h>

#include "types.h"

#define SIZE_OF_QUOTE  18

size_t fd_format_quotes(char* buffer, fd_rdd_data* data);

#endif /* _FINANCE_DISPLAY_FORMAT_H_ */
