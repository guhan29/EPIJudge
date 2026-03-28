#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
void RotateMatrix(vector<vector<int>>* square_matrix_ptr) {
  vector<vector<int>>& square_matrix = *square_matrix_ptr;
  int n = square_matrix.size();

  for (int i = 0; i < n / 2; i++) {
    for (int j = i; j < n - i - 1; j++) {
      int temp = square_matrix[i][j];
      square_matrix[i][j] = square_matrix[n - 1 - j][i];
      square_matrix[n - 1 - j][i] = square_matrix[n - 1 - i][n - 1 - j];
      square_matrix[n - 1 - i][n - 1 - j] = square_matrix[j][n - 1 - i];
      square_matrix[j][n - 1 - i] = temp;
    }
  }
}
vector<vector<int>> RotateMatrixWrapper(vector<vector<int>> square_matrix) {
  RotateMatrix(&square_matrix);
  return square_matrix;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "matrix_rotation.cc", "matrix_rotation.tsv",
                         &RotateMatrixWrapper, DefaultComparator{},
                         param_names);
}
