#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::bind;
using std::iota;
using std::vector;
using std::unordered_map;
// Returns a random k-sized subset of {0, 1, ..., n - 1}.
vector<int> RandomSubset(int n, int k) {
  unordered_map<int, int> elmap;
  for (int i = 0; i < k; i++) {
    int rand_idx = i + rand() % (n - i);
    int rand_mapped_idx = (elmap.find(rand_idx) == elmap.end() ? rand_idx : elmap[rand_idx]);
    int i_mapped = (elmap.find(i) == elmap.end() ? i : elmap[i]);
    elmap[rand_idx] = i_mapped;
    elmap[i] = rand_mapped_idx;
  }

  vector<int> res(k);
  for (int i = 0; i < k; i++)
    res[i] = elmap[i];
  return res;
}
bool RandomSubsetRunner(TimedExecutor& executor, int n, int k) {
  using namespace test_framework;
  vector<vector<int>> results;

  executor.Run([&] {
    std::generate_n(back_inserter(results), 100000,
                    std::bind(RandomSubset, n, k));
  });

  int total_possible_outcomes = BinomialCoefficient(n, k);
  vector<int> A(n);
  iota(begin(A), end(A), 0);
  vector<vector<int>> combinations;
  for (int i = 0; i < BinomialCoefficient(n, k); ++i) {
    combinations.emplace_back(ComputeCombinationIdx(A, n, k, i));
  }
  vector<int> sequence;
  for (vector<int> result : results) {
    sort(begin(result), end(result));
    sequence.emplace_back(
        distance(begin(combinations),
                 find(begin(combinations), end(combinations), result)));
  }
  return CheckSequenceIsUniformlyRandom(sequence, total_possible_outcomes,
                                        0.01);
}

void RandomSubsetWrapper(TimedExecutor& executor, int n, int k) {
  RunFuncWithRetries(bind(RandomSubsetRunner, std::ref(executor), n, k));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "n", "k"};
  return GenericTestMain(args, "random_subset.cc", "random_subset.tsv",
                         &RandomSubsetWrapper, DefaultComparator{},
                         param_names);
}
