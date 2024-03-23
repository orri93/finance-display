#include "format.h"

#define NUMBER_FORMAT_BUFFER_SIZE 16

static char nfb[NUMBER_FORMAT_BUFFER_SIZE];

static size_t fd_format_quote(char* buffer, fd_quote* quote);

size_t fd_format_quotes(char* buffer, fd_rdd_data* data) {
  size_t total = 0;
  for (int i = 0; i < data->count; i++) {
    size_t fqz = fd_format_quote(buffer, &(data->quotes[i]));
    buffer += fqz;
    total += fqz;
    *buffer = ' ';
    buffer++;
    total++;
  }
  return total;
}

size_t fd_format_quote(char* buffer, fd_quote* quote) {
  size_t len = strlen(quote->symbol);
  strcpy(buffer, quote->symbol);
  buffer += len;
  *buffer = ':';
  buffer++;
  len++;

  dtostrf(quote->price, 0, 4, nfb);
  size_t nlen = strlen(nfb);
  strcpy(buffer, nfb);
  buffer += nlen;
  len += nlen;
  if (quote->change > 0) {
    *buffer = 1;
    buffer++;
    len++;
  } else if (quote->change < 0) {
    *buffer = 2;
    buffer++;
    len++;
  }

  return len;
}
