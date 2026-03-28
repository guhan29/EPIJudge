#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsPalindromic(const string& s) {
  int n = s.size();
  for (int i = 0; i < n / 2; i++) {
    if (s[i] != s[n - i - 1]) return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic.cc",
                         "is_string_palindromic.tsv", &IsPalindromic,
                         DefaultComparator{}, param_names);
}
