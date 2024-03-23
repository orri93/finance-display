#include <Arduino_JSON.h>

#include "parse.h"

static double parse_double(JSONVar object, const char* key) {
  if (object.hasOwnProperty(key)) {
    return (double)object[key];
  } else {
    return 0.0;
  }
}

static bool parse_bool(JSONVar object, const char* key) {
  if (object.hasOwnProperty(key)) {
    return (bool)object[key];
  } else {
    return false;
  }
}

void parse_rdd_result(fd_rdd_data* data, const String& payload) {
  JSONVar rddObject = JSON.parse(payload);
  JSONVar marketStatusObject = rddObject["marketStatus"];
  data->market_status.open = parse_bool(marketStatusObject, "open");
  if (rddObject.hasOwnProperty("quoteList")) {
    JSONVar quoteListArray = rddObject["quoteList"];
    int length = quoteListArray.length();
    if (data->count != length) {
      if (data->count > 0) {
        delete[] data->quotes;
      }
      data->quotes = new fd_quote[length];
      data->count = length;
    }
    for (int i = 0; i < length; i++) {
      JSONVar quoteObject = quoteListArray[i];
      if (quoteObject.hasOwnProperty("symbol")) {
        const char* symbolText = (const char*)quoteObject["symbol"];
        strncpy(data->quotes[i].symbol, symbolText, SYMBOL_TEXT_SIZE);
      }
      data->quotes[i].price = parse_double(quoteObject, "price");
      data->quotes[i].change = parse_double(quoteObject, "change");
    }
  }
}
