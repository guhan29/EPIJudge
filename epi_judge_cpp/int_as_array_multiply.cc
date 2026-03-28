#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::abs;

vector<int> Multiply(vector<int> num1, vector<int> num2) {
  int n1 = num1.size(), n2 = num2.size();
  int sign = (num1[0] < 0) ^ (num2[0] < 0) ? -1 : 1;
  num1[0] = abs(num1[0]);
  num2[0] = abs(num2[0]);

  vector<int> res(n1 + n2, 0);
  for (int i = n1 - 1; i >= 0; i--) {
    for (int j = n2 - 1; j >= 0; j--) {
      res[i + j + 1] += num1[i] * num2[j];
      res[i + j] += res[i + j + 1] / 10;
      res[i + j + 1] %= 10;
    }
  }
  for (int i = 0; i < n1 + n2; i++) {
    if (res[i] != 0) {
      res = vector<int>(res.begin() + i, res.end());
      res[0] *= sign;
      return res;
    }
  }
  return {0};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
