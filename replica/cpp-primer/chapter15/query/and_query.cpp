#include "and_query.h"

#include <algorithm>

QueryResult AndQuery::Eval(TextQuery const& text) const {
  auto left{lhs.Eval(text)}, right{rhs.Eval(text)};

  auto ret_lines{std::make_shared<std::set<line_no>>()};

  std::set_intersection(left.Begin(), left.End(), right.Begin(), right.End(),
                        std::inserter(*ret_lines, ret_lines->begin()));

  return QueryResult(Rep(), ret_lines, left.GetFile());
}
