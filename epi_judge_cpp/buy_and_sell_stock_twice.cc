#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::min;
using std::max;
double BuyAndSellStockTwice(const vector<double>& prices) {
  double max_profit = 0.0;
  int n = prices.size();
  double min_so_far = prices[0], max_so_far = prices[n - 1];
  vector<double> first_buy(n, 0.0);
  for (int i = 0; i < n; i++) {
    min_so_far = min(min_so_far, prices[i]);
    max_profit = max(max_profit, prices[i] - min_so_far);
    first_buy[i] = max_profit;
  }
  for (int i = n - 1; i > 0; i--) {
    max_so_far = max(max_so_far, prices[i]);
    max_profit = max(max_profit, first_buy[i - 1] + max_so_far - prices[i]);
  }
  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
