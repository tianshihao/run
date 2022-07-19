#include "or_query.h"

QueryResult OrQuery::Eval(TextQuery const& text) const {
  // Virtual calls through the Query members, lhs and rhs the calls to Eval
  // return the QueryResult for each operand.
  auto left{lhs.Eval(text)};
  auto right{rhs.Eval(text)};

  // Copy the line numbers from the left-hand operand into the result set.
  auto ret_lines{std::make_shared<std::set<line_no>>(left.Begin(), left.End())};
  // Insert lines from the right-hand operand.
  ret_lines->insert(right.Begin(), right.End());
  // Return the new QueryResult representing the union of lhs and rhs.
  return QueryResult(Rep(), ret_lines, left.GetFile());
}
