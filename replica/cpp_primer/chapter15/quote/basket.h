#pragma once

#include <memory>
#include <set>

#include "quote.h"

class Basket {
 public:
  // Basket uses synthesized default constructor and copy-control members.
  void AddItem(const std::shared_ptr<Quote> &sale) {
    items.insert(sale);
    return;
  }

  // Copy the given object.
  void AddItem(const Quote &sale) {
    items.insert(std::shared_ptr<Quote>(sale.Clone()));
  }

  // Move the given object.
  void AddItem(Quote &&sale) {
    items.insert(std::shared_ptr<Quote>(std::move(sale).Clone()));
  }

  // Print total price for each book and the overall total for all items in the
  // basket.
  double TotalReceipt(std::ostream &) const;

 private:
  // Function to compare shared_ptr needed by the multiset member.
  static bool Compare(const std::shared_ptr<Quote> &lhs,
                      const std::shared_ptr<Quote> &rhs) {
    return lhs->ISBN() < rhs->ISBN();
  }

  // Multiset to hold multiple quotes, ordered byy the compare member.
  std::multiset<std::shared_ptr<Quote>, decltype(Compare) *> items{Compare};
};
