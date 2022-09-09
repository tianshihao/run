#include "../include/text_query.h"

#include <sstream>

/**
 * @brief Read the input file and build the map of lines to line number.
 * @param ifs Input file stream.
 */
TextQuery::TextQuery(std::ifstream &ifs) : file{new std::vector<std::string>} {
  std::string text;

  // For each line in file.
  while (getline(ifs, text)) {
    // Remeber this line of text.
    file->push_back(text);
    // The current line number.
    std::size_t cur_line_no{file->size() - 1};
    // Separator the line into words.
    std::istringstream line{text};
    std::string word;

    // For each word in that time.
    while (line >> word) {
      // If a word isn't already in word_map, subscripting adds a new entry.
      auto &lines{word_map[word]};
      // That pointer if null the first time we see word.
      if (nullptr == lines) {
        // Allocate a new set.
        lines.reset(new std::set<line_no>);
      }
      // Insert the line number.
      lines->insert(cur_line_no);
    }
  }
}

QueryResult TextQuery::Query(std::string const &sought) const {
  // We'll return a pointer.
  static std::shared_ptr<std::set<line_no>> nodata{new std::set<line_no>};

  // Use find and not a subscript to avoid adding words to word_map.
  auto loc{word_map.find(sought)};

  // Not found.
  if (word_map.end() == loc) {
    return QueryResult{sought, nodata, file};
  } else {
    return QueryResult{sought, loc->second, file};
  }
}
