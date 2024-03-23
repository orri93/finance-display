#ifndef _FINANCE_DISPLAY_PARSE_H_
#define _FINANCE_DISPLAY_PARSE_H_

#include <Arduino.h>

#include "types.h"

void parse_rdd_result(fd_rdd_data* data, const String& payload);

#endif /* _FINANCE_DISPLAY_PARSE_H_ */
