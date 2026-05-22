#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using std::swap;

int GetDepth(const unique_ptr<BinaryTreeNode<int>>& node) ;

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  int d0 = GetDepth(node0), d1 = GetDepth(node1);
  auto *iter0 = node0.get(), *iter1 = node1.get();

  if (d1 > d0) {
    swap(iter0, iter1);
  }
  int diff = abs(d0 - d1);
  while (diff--) {
    iter0 = iter0->parent;
  }
  while (iter0 != iter1) {
    iter0 = iter0->parent;
    iter1 = iter1->parent;
  }
  return iter0;
}

int GetDepth(const unique_ptr<BinaryTreeNode<int>>& node) {
  int depth = 0;
  auto iter = node.get();
  while (iter->parent) {
    iter = iter->parent;
    depth++;
  }
  return depth;
}

int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
