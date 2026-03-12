#include "test_framework/generic_test.h"
unsigned long long ReverseBits(unsigned long long x) {
  unsigned long long res = 0;
  /*
  for (int i = 0; i < 64; i++) {
    res <<= 1;
    res |= (x & 1);
    x >>= 1;
  }
  */

  res = x;
  res = ((res >> 1) & 0x5555555555555555) | ((res & 0x5555555555555555) << 1);
  res = ((res >> 2) & 0x3333333333333333) | ((res & 0x3333333333333333) << 2);
  res = ((res >> 4) & 0x0F0F0F0F0F0F0F0F) | ((res & 0x0F0F0F0F0F0F0F0F) << 4);
  res = ((res >> 8) & 0x00FF00FF00FF00FF) | ((res & 0x00FF00FF00FF00FF) << 8);
  res = ((res >> 16) & 0x0000FFFF0000FFFF) | ((res & 0x0000FFFF0000FFFF) << 16);
  res = ((res >> 32) & 0x00000000FFFFFFFF) | ((res & 0x00000000FFFFFFFF) << 32);
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
