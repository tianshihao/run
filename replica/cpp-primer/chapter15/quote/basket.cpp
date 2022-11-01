#include "basket.h"

#include <iostream>

double PrintTotal(std::ostream&, const Quote, std::size_t);

double Basket::TotalReceipt(std::ostream& os) const {
  double sum{0.0};

  // iter refers to the first element in a batch of elements with the same ISBN.
  // upper_bound returns an iterator to the element just past the end of that
  // batch.
  for (auto iter{items.cbegin()}; iter != items.cend();
       iter = items.upper_bound(*iter)) {
    // We know there's at least one element with this key in the Basket.
    // Print the line item for this book.
    sum += PrintTotal(os, **iter, items.count(*iter));
  }

  os << "Total Sale: " << sum << std::endl;

  return sum;
}
