#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::swap;
void ApplyPermutation(vector<int> perm, vector<int>* A_ptr) {
  vector<int>& A = *A_ptr;
  int n = A.size();
  for (int i = 0; i < n; i++) {
    int next = i;
    while (perm[next] >= 0) {
      swap(A[i], A[perm[next]]);
      int temp = perm[next];
      perm[next] -= n;
      next = temp;
    }
  }
}
vector<int> ApplyPermutationWrapper(const vector<int>& perm, vector<int> A) {
  ApplyPermutation(perm, &A);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm", "A"};
  return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
                         &ApplyPermutationWrapper, DefaultComparator{},
                         param_names);
}
