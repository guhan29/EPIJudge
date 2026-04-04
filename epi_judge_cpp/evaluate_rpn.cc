#include <string>

#include "test_framework/generic_test.h"
using std::string;

using std::stack;
using std::isdigit;
using std::stringstream;

int Evaluate(const string& expression) {
  stack<int> res;
  stringstream ss(expression);
  string token;
  const char delimiter = ',';
  while (getline(ss, token, delimiter)) {
    if (isdigit(token.front())) {
      res.push(stoi(token));
    } else {
      int b = res.top();
      res.pop();
      int a = res.top();
      res.pop();
      switch (token.front()) {
        case '+':
          res.push(a + b);
          break;
        case '-':
          res.push(a - b);
          break;
        case '*':
          res.push(a * b);
          break;
        case '/':
          res.push(a / b);
          break;
      }
    }
  }
  return res.top();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
