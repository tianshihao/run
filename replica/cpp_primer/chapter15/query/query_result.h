#pragma once

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

class QueryResult {
  friend std::ostream& Print(std::ostream&, QueryResult const&);

 public:
  using line_no = std::vector<std::string>::size_type;
  QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p,
              std::shared_ptr<std::vector<std::string>> f)
      : sought{s}, lines{p}, file{f} {}

  auto Begin() const { return lines->begin(); }
  auto End() const { return lines->end(); }
  auto GetFile() const { return file; }

 private:
  /// Word this query represents.
  std::string sought;
  /// Lines it's on.
  std::shared_ptr<std::set<line_no>> lines;
  /// Input file.
  std::shared_ptr<std::vector<std::string>> file;
};
