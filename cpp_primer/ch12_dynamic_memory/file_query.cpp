#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class QueryResult;

class TextQuery {
public:
  using line_no_type = std::vector<std::string>::size_type;
  TextQuery(std::ifstream &is);
  QueryResult query(const std::string &word);

private:
  std::shared_ptr<std::vector<std::string>> file;
  std::map<std::string, std::shared_ptr<std::set<line_no_type>>> wm;
};

// =============================================================================

class QueryResult {
  friend std::ostream &operator<<(std::ostream &os, const QueryResult &qr);

public:
  using line_no_type = std::vector<std::string>::size_type;
  QueryResult(const std::string &w, std::shared_ptr<std::set<line_no_type>> li,
              std::shared_ptr<std::vector<std::string>> f)
      : word(w), lines(li), file(f) {}

private:
  std::string word;
  std::shared_ptr<std::set<line_no_type>> lines;
  std::shared_ptr<std::vector<std::string>> file;
};

// =============================================================================

std::ostream &operator<<(std::ostream &os, const QueryResult &qr) {
  os << qr.word << " occurs " << qr.lines->size() << " times." << std::endl;
  for (auto x : *qr.lines) {
    os << "\t(line " << x + 1 << ")|" << *(qr.file->begin() + x) << "|"
       << std::endl;
  }

  return os;
}

// =============================================================================

TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>()) {
  std::string line;
  while (std::getline(is, line)) {
    file->push_back(line);
    int n = file->size() - 1;
    std::istringstream iss(line);
    std::string word;
    while (iss >> word) {
      auto &ptr = wm[word];
      if (!ptr) {
        ptr.reset(new std::set<line_no_type>);
      }
      ptr->insert(n);
    }
  }
}

QueryResult TextQuery::query(const std::string &word) {
  auto itr = wm.find(word);
  if (itr == wm.end()) {
    std::shared_ptr<std::set<line_no_type>> nodata(new std::set<line_no_type>);
    return QueryResult(word, nodata, file);
  } else {
    return QueryResult(word, itr->second, file);
  }
}

// =============================================================================

void runQueries(std::ifstream &is) {
  TextQuery tq(is);

  while (true) {
    std::cout << "Enter word to look for, or q to exit: ";
    std::string word;
    if (!(std::cin >> word) || word == "q")
      break;
    QueryResult qr = tq.query(word);
    std::cout << qr << std::endl;
  }
}

// =============================================================================

using namespace std;

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "usage: file_query <file_name>" << endl;
    return 1;
  }
  string filename(argv[1]);
  ifstream ifs(filename);

  runQueries(ifs);

  return 0;
}
