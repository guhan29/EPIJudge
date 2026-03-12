#include "test_framework/generic_test.h"

unsigned long long add(unsigned long long a, unsigned long long b) {
  unsigned long long tempA = a, tempB = b, carryIn = 0, k = 1;
  unsigned long long runningSum = 0;

  while (tempA || tempB) {
    unsigned long long ak = a & k, bk = b & k;
    unsigned long long carryOut = (ak & bk) | (ak & carryIn) | (bk & carryIn);
    runningSum |= ak ^ bk ^ carryIn;

    carryIn = carryOut << 1;
    k <<= 1;
    tempA >>= 1;
    tempB >>= 1;
  }
  return runningSum | carryIn;
}

unsigned long long Multiply(unsigned long long x, unsigned long long y) {
  unsigned long long sum = 0;
  while (x) {
    if (x & 1) {
      sum = add(sum, y);
    }
    x >>= 1;
    y <<= 1;
  }
  return sum;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "primitive_multiply.cc",
                         "primitive_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
