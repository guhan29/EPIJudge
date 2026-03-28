#include <string>

#include "test_framework/generic_test.h"
using std::string;

string ConstructString(int, int);

string ConvertBase(const string& num_as_string, int b1, int b2) {
  int num_as_int = 0;
  bool is_neg = num_as_string.front() == '-';
  for (int i = is_neg; i < num_as_string.size(); i++) {
    num_as_int *= b1;
    num_as_int += isdigit(num_as_string[i]) ? num_as_string[i] - '0' 
                                            : num_as_string[i] - 'A' + 10;
  }
  return (is_neg ? "-" : "") 
        + (num_as_int == 0 ? "0" : ConstructString(num_as_int, b2));
}

string ConstructString(int num, int b) {
  string res = "";
  while (num) {
    res = (char)((num % b >= 10) ? 'A' + (num % b - 10) 
                                  : '0' + (num % b)) + res;
    num /= b;
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
