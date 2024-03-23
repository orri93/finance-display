#ifndef _FINANCE_DISPLAY_TYPES_H_
#define _FINANCE_DISPLAY_TYPES_H_

#define SYMBOL_TEXT_SIZE 6

typedef struct fd_quote {
  char symbol[SYMBOL_TEXT_SIZE];
  double price;
  double change;
} fd_quote;

typedef struct fd_market_status {
  bool open;
} fd_market_status;

typedef struct fd_rdd_data {
  fd_market_status market_status;
  fd_quote* quotes;
  int count;
} fd_rdd_data;

#endif /* _FINANCE_DISPLAY_TYPES_H_ */