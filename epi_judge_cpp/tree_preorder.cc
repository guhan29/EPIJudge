#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::vector;

using std::stack;

vector<int> PreorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  stack<BinaryTreeNode<int>*> s;
  s.push(tree.get());
  vector<int> res;

  while (!s.empty()) {
    auto curr = s.top();
    s.pop();

    if (curr) {
      res.emplace_back(curr->data);
      s.emplace(curr->right.get());
      s.emplace(curr->left.get());
    }
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_preorder.cc", "tree_preorder.tsv",
                         &PreorderTraversal, DefaultComparator{}, param_names);
}
