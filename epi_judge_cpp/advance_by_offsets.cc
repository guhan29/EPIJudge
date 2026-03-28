#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::max;

bool CanReachEnd(const vector<int>& max_advance_steps) {
  int max_reach = 0;
  int i = 0, n = max_advance_steps.size();
  while (i <= max_reach && i < n - 1) {
    max_reach = max(max_reach, i + max_advance_steps[i]);
    i++;
  }
  return max_reach >= n - 1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"max_advance_steps"};
  return GenericTestMain(args, "advance_by_offsets.cc",
                         "advance_by_offsets.tsv", &CanReachEnd,
                         DefaultComparator{}, param_names);
}
