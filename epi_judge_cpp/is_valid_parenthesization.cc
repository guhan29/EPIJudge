#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;

using std::stack;
using std::unordered_map;

bool IsWellFormed(const string& s) {
  stack<char> stk;
  unordered_map<char, char> pMap = {{'{', '}'}, {'(', ')'}, {'[', ']'}};
  for (const char& ch : s) {
    if (pMap.find(ch) == pMap.end()) {
      if (!stk.empty() && pMap[stk.top()] == ch) {
        stk.pop();
      } else {
        return false;
      }
    } else {
      stk.push(ch);
    }
  }
  return stk.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
