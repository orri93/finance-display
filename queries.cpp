#include "queries.h"
#include "configuration.h"

#define QUERY_PREFIX  "http://"

const char* create_quotes_query() {
  return QUERY_PREFIX FINANCE_SERVICE_HOST ":" FINANCE_SERVICE_PORT "/rdd";
}
