#include "rdd.h"

void init_rdd_data(fd_rdd_data* data) {
  data->market_status.open = false;
  data->quotes = nullptr;
  data->count = 0;
}
