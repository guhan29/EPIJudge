#include <vector>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  BinaryTreeNode<int>* prev = nullptr, *curr = tree.get();
  vector<int> result;
  while (curr != nullptr) {
    BinaryTreeNode<int>* next;
    if (curr->parent == prev) {
      if (curr->left != nullptr) {
        next = curr->left.get();
      } else {
        result.emplace_back(curr->data);
        next = (curr->right != nullptr) ? curr->right.get() : curr->parent;
      }
    } else if (curr->left.get() == prev) {
      result.emplace_back(curr->data);
      next = (curr->right != nullptr) ? curr->right.get() : curr->parent;
    } else {
      next = curr->parent;
    }

    prev = curr;
    curr = next;
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
