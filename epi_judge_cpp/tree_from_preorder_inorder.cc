#include <vector>
#include <unordered_map>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
using std::vector;

using std::unordered_map;
using std::make_unique;

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorderHelper(
  const vector<int>& preorder, 
  int preorder_start, 
  int preorder_end, 
  const vector<int>& inorder,
  int inorder_start,
  int inorder_end,
  const unordered_map<int, int>& inorder_map);

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {
  unordered_map<int, int> inorder_map;
  for (int i = 0; i < inorder.size(); i++) {
    inorder_map[inorder[i]] = i;
  }
  return BinaryTreeFromPreorderInorderHelper(preorder, 
    0, preorder.size(), inorder, 0, inorder.size(), inorder_map);
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorderHelper(
  const vector<int>& preorder, 
  int preorder_start, 
  int preorder_end, 
  const vector<int>& inorder,
  int inorder_start,
  int inorder_end,
  const unordered_map<int, int>& inorder_map) {

  if (preorder_start >= preorder_end || inorder_start >= inorder_end) return nullptr;

  int root_inorder_idx = inorder_map.at(preorder[preorder_start]);
  int left_subtree_size = root_inorder_idx - inorder_start;

  return make_unique<BinaryTreeNode<int>>(
    preorder[preorder_start],
    BinaryTreeFromPreorderInorderHelper(preorder, 
      preorder_start + 1, 
      preorder_start + 1 + left_subtree_size,
      inorder,
      inorder_start,
      root_inorder_idx,
      inorder_map),
    BinaryTreeFromPreorderInorderHelper(preorder,
      preorder_start + 1 + left_subtree_size,
      preorder_end,
      inorder,
      root_inorder_idx + 1,
      inorder_end,
      inorder_map)
  );
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
