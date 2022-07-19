#pragma once

#include <string>

#include "query.h"
#include "text_query.h"

/**
 * @brief Abstract class acts a base class for concrete query types; All members
 * are private. Because we don't intend users, or the derived classes, to the
 * QueryBase directly, QueryBase has no public members. All use of QueryBase
 * will be through Query objects. We grant friendship to the Query class,
 * because members of Query will call the virtuals in QueryBase.
 */
class QueryBase {
  friend class Query;

 protected:
  using line_no = TextQuery::line_no;
  virtual ~QueryBase() = default;

 private:
  /// Eval returns the QueryResult that matches this Query.
  virtual QueryResult Eval(TextQuery const &) const = 0;
  /// Rep is a string representation of the query.
  virtual std::string Rep() const = 0;
};
