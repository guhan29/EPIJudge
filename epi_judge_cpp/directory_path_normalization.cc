#include <string>
#include <stack>

#include "test_framework/generic_test.h"
using std::string;

using std::stringstream;
using std::stack;
// using std::getline;

string ShortestEquivalentPath(const string& path) {
  if (path.empty()) return "";

  stack<string> path_stack;
  if (path.front() == '/') {
    path_stack.push("/");
  }

  stringstream ss(path);
  string token;
  while (getline(ss, token, '/')) {
    if (token == "..") {
      if (path_stack.empty() || path_stack.top() == "..") path_stack.push(token);
      else if (path_stack.top() == "/") return "";
      else path_stack.pop();
    } else if (token != "." && token != "") {
      path_stack.push(token);
    }
  }
  string res;
  while (!path_stack.empty()) {
    res = path_stack.top() + "/" + res;
    path_stack.pop();
  }
  res.pop_back();
  if (res.substr(0, 2) == "//") res = res.substr(1);
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"path"};
  return GenericTestMain(args, "directory_path_normalization.cc",
                         "directory_path_normalization.tsv",
                         &ShortestEquivalentPath, DefaultComparator{},
                         param_names);
}
