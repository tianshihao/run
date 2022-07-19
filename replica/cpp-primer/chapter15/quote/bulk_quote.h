#pragma once

#include "disc_quote.h"

class BulkQuote : public DiscQuote {
 public:
  BulkQuote() = default;
  BulkQuote(const std::string& book, double price, std::size_t qty, double disc)
      : DiscQuote{book, price, qty, disc} {}

  BulkQuote* Clone() const& override { return new BulkQuote(*this); }
  BulkQuote* Clone() && override { return new BulkQuote(std::move(*this)); }

  double NetPrice(std::size_t) const override;
};
