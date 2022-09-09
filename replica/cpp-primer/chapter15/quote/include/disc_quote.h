#pragma once

#include "./quote.h"

/**
 * @brief Class to hold the discount rate and quanlity. Dirived classes will
 * implement pricing strategies using these data.
 */
class DiscQuote : public Quote {
 public:
  DiscQuote() = default;
  DiscQuote(const std::string& book, double price, std::size_t qty, double disc)
      : Quote{book, price}, quantity{qty}, discount{disc} {}

  double NetPrice(std::size_t) const = 0;

  std::pair<std::size_t, double> DiscountPolicy() const {
    return {quantity, discount};
  }

  // Why those member need to be protected?
 protected:
  std::size_t quantity = 0;
  double discount = 0.0;
};
