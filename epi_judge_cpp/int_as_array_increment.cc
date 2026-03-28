#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  int n = A.size();
  A[n - 1]++;
  for (int i = n - 1; i > 0 && A[i] == 10; i--) {
    A[i - 1]++;
    A[i] = 0;
  }
  if (A[0] == 10) {
    A[0] = 1;
    A.push_back(0);
  }
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
