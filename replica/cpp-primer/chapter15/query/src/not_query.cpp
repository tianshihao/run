#include "../include/not_query.h"

QueryResult NotQuery::Eval(TextQuery const& text) const {
  auto result{query.Eval(text)};

  auto ret_lines{std::make_shared<std::set<line_no>>()};
  auto beg{result.Begin()}, end{result.End()};

  auto sz{result.GetFile()->size()};
  for (auto n{static_cast<size_t>(0)}; n != sz; ++n) {
    if (beg == end || *beg != n) {
      ret_lines->insert(n);
    } else if (beg != end) {
      ++beg;
    }
  }

  return QueryResult(Rep(), ret_lines, result.GetFile());
}
