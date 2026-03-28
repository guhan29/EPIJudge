#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
using std::max;
using std::min;
double BuyAndSellStockOnce(const vector<double>& prices) {
  double min_so_far = prices[0], profit = 0;
  for (const double price : prices) {
    profit = max(profit, price - min_so_far);
    min_so_far = min(min_so_far, price);
  }
  return profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
