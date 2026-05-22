#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

int SumRootToLeafHelper(const unique_ptr<BinaryTreeNode<int>>& tree, int partial_sum);

int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
  return SumRootToLeafHelper(tree, 0);
}

int SumRootToLeafHelper(const unique_ptr<BinaryTreeNode<int>>& root, int partial_sum) {
  if (!root) return 0;

  partial_sum = 2 * partial_sum + root->data;
  
  if (root->left == nullptr && root->right == nullptr) 
    return partial_sum;

  return SumRootToLeafHelper(root->left, partial_sum) +
    SumRootToLeafHelper(root->right, partial_sum);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "sum_root_to_leaf.cc", "sum_root_to_leaf.tsv",
                         &SumRootToLeaf, DefaultComparator{}, param_names);
}
