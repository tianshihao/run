#pragma once

#include <memory>
#include <string>

#include "binary_query.h"
#include "query.h"
#include "query_base.h"
#include "query_result.h"

class AndQuery final : public BinaryQuery {
  friend Query operator&(Query const &, Query const &);

 private:
  AndQuery(Query const &left, Query const &right)
      : BinaryQuery{left, right, "&"} {}

  QueryResult Eval(TextQuery const &) const final;
};
