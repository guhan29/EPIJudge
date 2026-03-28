#include <string>

#include "test_framework/generic_test.h"
using std::string;
using std::to_string;

string NextNumber(const string&);

string LookAndSay(int n) {
  string s = "1";
  for (int i = 1; i < n; i++) {
    s = NextNumber(s);
  }
  return s;
}

string NextNumber(const string& s) {
  string res;
  int i = 0, n = s.size();
  while (i < n) {
    int count = 1;
    while (i + 1 < n && s[i] == s[i + 1]) {
      count++;
      i++;
    }
    res += to_string(count) + s[i];

    i++;
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
