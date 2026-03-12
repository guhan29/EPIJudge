#include "test_framework/generic_test.h"
int Divide(int x, int y) {
  int res = 0, power = 32;
  long long y_power = (long long) y << power;
  while (x >= y) {
    while (y_power > x) {
      y_power >>= 1;
      power -= 1;
    }
    res += 1 << power;
    x -= y_power;
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_divide.cc", "primitive_divide.tsv",
                         &Divide, DefaultComparator{}, param_names);
}
