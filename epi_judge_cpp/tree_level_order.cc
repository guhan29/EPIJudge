#include <memory>
#include <vector>
#include <queue>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;
using std::queue;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<vector<int>> res;
  if (!tree) return res;

  queue<BinaryTreeNode<int>*> q;
  q.push(tree.get());

  while (!q.empty()) {
    int n = q.size();
    vector<int> level;
    for (int i = 0; i < n; i++) {
      auto node = q.front();
      level.emplace_back(node->data);
      q.pop();

      if (node->left) {
        q.push(node->left.get());
      }
      if (node->right) {
        q.push(node->right.get());
      }
    }
    res.emplace_back(level);
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
