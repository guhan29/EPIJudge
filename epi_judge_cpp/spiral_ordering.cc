#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
  vector<int> spiral_ordering;
  int n = square_matrix.size();
  int r_begin = 0, r_end = n - 1, c_begin = 0, c_end = n - 1;
  
  while(r_begin <= r_end && c_begin <= c_end) {
    for (int j = c_begin; j <= c_end; j++) spiral_ordering.push_back(square_matrix[r_begin][j]);
    r_begin++;
    for (int i = r_begin; i <= r_end; i++) spiral_ordering.push_back(square_matrix[i][c_end]);
    c_end--;

    if (r_begin > r_end || c_begin > c_end) break;

    for (int j = c_end; j >= c_begin; j--) spiral_ordering.push_back(square_matrix[r_end][j]);
    r_end--;
    for (int i = r_end; i >= r_begin; i--) spiral_ordering.push_back(square_matrix[i][c_begin]);
    c_begin++;
  }
  return spiral_ordering;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
