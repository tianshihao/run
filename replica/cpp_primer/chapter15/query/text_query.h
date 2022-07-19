#pragma once

#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "query_result.h"

/**
 * @brief Declaration needed for return type in the query function.
 * class QueryResult;
 */
class TextQuery {
 public:
  using line_no = std::vector<std::string>::size_type;

  TextQuery(std::ifstream&);
  QueryResult Query(std::string const&) const;

 private:
  /// Input file.
  std::shared_ptr<std::vector<std::string>> file;
  /// Map of each word to the set of the lines in which that word appears.
  std::map<std::string, std::shared_ptr<std::set<line_no>>> word_map;
};
