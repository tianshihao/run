#pragma once

#include <string>

#include "query.h"
#include "query_base.h"
#include "query_result.h"
#include "text_query.h"

class WordQuery final : public QueryBase {
  /// WordQuery must make Query a friend in order to allow Query to access the
  /// WordQuery constructor.
  friend class Query;

 private:
  WordQuery(std::string const& s) : query_word{s} {}

  /// Concrete class: WordQuery defines all inherited pure vitual functions.

  QueryResult Eval(TextQuery const& t) const final{
    return t.Query(query_word);
  }
  std::string Rep() const final { return query_word; }

  /// Word for which to search.
  std::string query_word;
};
