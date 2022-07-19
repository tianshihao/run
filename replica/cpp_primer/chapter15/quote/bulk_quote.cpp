#include "bulk_quote.h"

double BulkQuote::NetPrice(std::size_t cnt) const {
  if (cnt >= quantity) {
    return cnt * (1 - discount) * price;
  } else {
    return cnt * price;
  }
}
