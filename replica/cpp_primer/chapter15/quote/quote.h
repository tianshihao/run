#pragma once

#include <string>

class Quote {
 public:
  Quote() = default;
  Quote(const Quote &) = default;
  Quote(Quote &&) = default;
  Quote &operator=(const Quote &) = default;
  Quote &operator=(Quote &&) = default;
  virtual ~Quote() = default;

  Quote(const std::string &book, double sales_price)
      : book_no{book}, price{sales_price} {}

  // Virtual function return a dynamically allocated copy of itself.
  // These members use reference qualifiers.
  virtual Quote *Clone() const & { return new Quote(*this); }
  virtual Quote *Clone() && { return new Quote(std::move(*this)); }

  std::string ISBN() const { return book_no; }
  virtual double NetPrice(std::size_t n) const { return n * price; }

 private:
  std::string book_no;

 protected:
  double price = 0.0f;
};
