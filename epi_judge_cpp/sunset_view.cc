#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

using std::stack;
vector<int> ExamineBuildingsWithSunset(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end) {

  struct Building {
    int id;
    int height;
  };
  int index = 0;
  stack<Building> stk;
  for (auto it = sequence_begin; it != sequence_end; it++) {
    while (!stk.empty() && stk.top().height <= *it) stk.pop();
    stk.push({index, *it});
    index++;
  }

  vector<int> res;
  while (!stk.empty()) {
    res.emplace_back(stk.top().id);
    stk.pop();
  }
  return res;
}
vector<int> ExamineBuildingsWithSunsetWrapper(const vector<int>& sequence) {
  return ExamineBuildingsWithSunset(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "sunset_view.cc", "sunset_view.tsv",
                         &ExamineBuildingsWithSunsetWrapper,
                         DefaultComparator{}, param_names);
}
