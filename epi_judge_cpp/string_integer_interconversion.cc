#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  string res = "";
  bool is_neg = false;
  if (x < 0) {
    is_neg = true;
  }
  do {
    res += '0' + abs(x % 10);
    x /= 10;
  } while (x != 0);
  if (is_neg) res += "-";
  reverse(res.begin(), res.end());
  return res;
}
int StringToInt(const string& s) {
  bool is_neg = false;
  int num = 0, i = 0, n = s.size();
  if (s[0] == '-') {
    is_neg = true;
  }
  i = (s[i] == '-' || s[i] == '+');
  while (i < n) {
    num = num * 10 + -(s[i] - '0');
    i++;
  }
  num *= (is_neg ? 1 : -1);
  return num;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
