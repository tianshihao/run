#pragma once

#include <memory>
#include <string>

#include "query_base.h"
#include "query_result.h"
#include "text_query.h"
#include "word_query.h"

/// @brief Interface class that points to an object of a type derived from
/// QueryBase to manege the QueryBase inheritance hirarchy. Each Query object
/// will hold a shared_ptr to a corresponding QueryBase object.
class Query {
  /// Thoses operators need access to the shared_ptr constructor.
  friend Query operator~(Query const &);
  friend Query operator|(Query const &, Query const &);
  friend Query operator&(Query const &, Query const &);

 public:
  /// Builds a new word query.
  Query(std::string const &s) : sp_query_base{new WordQuery(s)} {}
  /// Interface functions: call the corresponding QueryBase operations.
  /// Because Query is the only interface to the QueryBase classes, Query must
  /// define its own versions of Eval and Rep.
  QueryResult Eval(TextQuery const &t) const { return sp_query_base->Eval(t); }
  std::string Rep() const { return sp_query_base->Rep(); }

 private:
  /// We will make this constructor private because we don't intend general user
  /// code to define QueryBase objects. Because this constructor is private,
  /// we'll need to make the operators friends.
  Query(std::shared_ptr<QueryBase> query) : sp_query_base{query} {}
  std::shared_ptr<QueryBase> sp_query_base;
};
