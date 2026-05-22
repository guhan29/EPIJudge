#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

bool IsSymmetricHelper(const unique_ptr<BinaryTreeNode<int>>& left_tree, 
  const unique_ptr<BinaryTreeNode<int>>& right_tree);

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return tree == nullptr || IsSymmetricHelper(tree->left, tree->right);
}

bool IsSymmetricHelper(const unique_ptr<BinaryTreeNode<int>>& left_tree, 
  const unique_ptr<BinaryTreeNode<int>>& right_tree) {
  if (left_tree == nullptr && right_tree == nullptr) return true;
  else if (left_tree != nullptr && right_tree != nullptr) {
    return left_tree->data == right_tree->data && 
      IsSymmetricHelper(left_tree->left, right_tree->right) &&
      IsSymmetricHelper(left_tree->right, right_tree->left);
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
