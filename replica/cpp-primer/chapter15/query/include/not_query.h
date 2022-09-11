#pragma once

#include <memory>
#include <string>

#include "query.h"
#include "query_base.h"
#include "query_result.h"
#include "text_query.h"

/// @brief
class NotQuery final: public QueryBase {
  friend Query operator~(Query const &);

 private:
  NotQuery(Query const &q) : query{q} {}

  // Concrete class: NotQuery defines all inherited pure virtual functions.

  QueryResult Eval(TextQuery const &) const final;

  std::string Rep() const final { return "~(" + query.Rep() + ")"; }

  Query query;
};
