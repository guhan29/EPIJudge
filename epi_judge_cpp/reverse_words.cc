#include <string>
#include <algorithm>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::swap;

void ReverseStr(string&, int, int);

void ReverseWords(string* s) {
  string& str = *s;
  int n = str.size();

  ReverseStr(str, 0, n - 1);
  
  int start = 0, finish = 0;
  while (finish < n) {
    while (str[finish] != ' ' && finish < n) finish++;
    ReverseStr(str, start, finish - 1);
    finish++;
    start = finish;
  }
}

void ReverseStr(string& s, int start, int end) {
  while (start < end) {
    swap(s[start++], s[end--]);
  }
}

string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}
