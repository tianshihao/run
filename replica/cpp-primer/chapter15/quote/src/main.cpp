#include <iostream>
#include <memory>

#include "../include/basket.h"
#include "../include/bulk_quote.h"
#include "../include/disc_quote.h"
#include "../include/quote.h"

double PrintTotal(std::ostream&, const Quote, std::size_t);

int main(int argc, char** argv) {
  BulkQuote bq{"Flow my tears, the policeman said", 40.0, 10, 0.2};
  
  Basket bsk;
  bsk.AddItem(std::make_shared<Quote>("Foundation", 30.0));
  bsk.AddItem(std::make_shared<BulkQuote>("Hyperion", 100.0, 3, 0.8));
  bsk.AddItem(std::make_shared<Quote>("Neon Genesis Evangelion", 200.0));
  bsk.AddItem(std::make_shared<Quote>("Neon Genesis Evangelion", 200.0));

  bsk.AddItem(bq);

  bsk.TotalReceipt(std::cout);

  return 0;
}

double PrintTotal(std::ostream& os, const Quote item, std::size_t n) {
  double ret{item.NetPrice(n)};
  os << "ISBN: " << item.ISBN() << " # sold: " << n << " total due: " << ret
     << std::endl;
  return ret;
}
