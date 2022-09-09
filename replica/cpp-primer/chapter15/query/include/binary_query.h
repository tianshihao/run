#pragma once

#include <memory>
#include <string>

#include "query.h"
#include "query_base.h"
#include "query_result.h"
#include "text_query.h"

/// @brief The BinaryQuery class is an abstract base class that holds the data
/// needed by the query types that operate on two operands.
class BinaryQuery : public QueryBase {
 protected:
  BinaryQuery(Query const& l, Query const& r, std::string const s)
      : lhs{l}, rhs{r}, op_sym{s} {}

  std::string Rep() const final {
    return "(" + lhs.Rep() + " " + op_sym + " " + rhs.Rep() + ")";
  }

  /// Left- and right-hand operands.
  Query lhs, rhs;
  /// Name of the operator.
  std::string op_sym;
};
