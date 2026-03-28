#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::swap;
using std::reverse;
vector<int> NextPermutation(vector<int> perm) {
  int n = perm.size();
  int inversion_point = n - 2;
  while (inversion_point >= 0 && perm[inversion_point] >= perm[inversion_point + 1])
    inversion_point--;
  if (inversion_point == -1)  return {};

  for (int i = n - 1; i >= 0; i--) {
    if (perm[i] > perm[inversion_point]) {
      swap(perm[i], perm[inversion_point]);
      break;
    }
  }

  reverse(perm.begin() + inversion_point + 1, perm.end());
  return perm;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm"};
  return GenericTestMain(args, "next_permutation.cc", "next_permutation.tsv",
                         &NextPermutation, DefaultComparator{}, param_names);
}
