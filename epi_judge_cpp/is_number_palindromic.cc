#include <cmath>

#include "test_framework/generic_test.h"
bool IsPalindromeNumber(int x) {
  if (x <= 0) return x == 0;

  /*
  int temp = x, rev = 0;
  while (temp) {
    rev = rev * 10 + (temp % 10);
    temp /= 10;
  }
  return x == rev;
  */
  int num_digits = static_cast<int>(floor(log10(x))) + 1;
  int mask = static_cast<int>(pow(10, num_digits - 1));
  for (int i = 0; i < num_digits / 2; i++) {
    if (x / mask != x % 10) return false;
    x %= mask;
    x /= 10;
    mask /= 100;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
