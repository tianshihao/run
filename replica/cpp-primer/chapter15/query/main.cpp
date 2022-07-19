#include <fstream>
#include <iostream>
#include <string>

#include "and_query.h"
#include "not_query.h"
#include "or_query.h"
#include "query.h"
#include "query_result.h"
#include "text_query.h"

void RunQueries(std::ifstream&);
std::ostream& Print(std::ostream&, QueryResult const&);
std::ostream& operator<<(std::ostream&, Query const&);
inline Query operator&(Query const&, Query const&);
inline Query operator|(Query const&, Query const&);
inline Query operator~(Query const&);

int main() {
  std::ifstream ifs{"example.txt"};
  RunQueries(ifs);

  return 0;
}

void RunQueries(std::ifstream& infile) {
  // infile is an ifstream that is the file we want to query.
  TextQuery tq{infile};

  Query q{Query("is") & (Query("in") | Query("the"))};

  Print(std::cout, q.Eval(tq));

  return;

  // Iterate with the user: prompt for a word to find and print results.
  while (true) {
    std::cout << "Enter word to look for, or q to quit: ";
    std::string s;
    if (!(std::cin >> s) || "q" == s) {
      break;
    }
    Print(std::cout, tq.Query(s)) << std::endl;
  }

  return;
}

std::ostream& Print(std::ostream& os, QueryResult const& qr) {
  // If the word was found, print the count and all occurences.
  os << qr.sought << " occurs " << qr.lines->size() << " "
     << "time(s)" << std::endl;

  // Print each line in which the word appeared.
  // For evey element in the set.
  for (auto num : *qr.lines) {
    // Don's confound the user with text lines starting at 0.
    os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num)
       << std::endl;
  }

  return os;
}

std::ostream& operator<<(std::ostream& os, Query const& query) {
  // Query::Rep makes a virtual call through its QueryBase pointer to Rep().
  return os << query.Rep();
}

inline Query operator&(Query const& lhs, Query const& rhs) {
  return std::shared_ptr<QueryBase>(new AndQuery(lhs, rhs));
}

inline Query operator|(Query const& lhs, Query const& rhs) {
  return std::shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
}

inline Query operator~(Query const& operand) {
  return std::shared_ptr<QueryBase>(new NotQuery(operand));
}
