#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

using std::max;

struct Pr {
  int height;
  bool balanced;
};

Pr checkBalanced(const unique_ptr<BinaryTreeNode<int>>&);

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return checkBalanced(tree).balanced;
}

Pr checkBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (!tree) return {-1, true};
  auto left = checkBalanced(tree->left);
  if (!left.balanced) {
    return {0, false};
  }
  auto right = checkBalanced(tree->right);
  if (!right.balanced) {
    return {0, false};
  }
  int height = max(left.height, right.height) + 1;
  bool balanced = abs(left.height - right.height) <= 1;
  return {height, balanced};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
