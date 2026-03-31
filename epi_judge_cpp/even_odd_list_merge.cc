#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  if (!L) return L;

  auto even_dummy_head = make_shared<ListNode<int>>(0), odd_dummy_head = make_shared<ListNode<int>>(0);
  auto even_tail = even_dummy_head, odd_tail = odd_dummy_head;
  bool turn = true;
  auto it = L;
  while (it) {
    if (turn) {
      even_tail->next = it;
      even_tail = even_tail->next;
    } else {
      odd_tail->next = it;
      odd_tail = odd_tail->next;
    }
    it = it->next;
    turn = !turn;
  }
  odd_tail->next = nullptr;
  even_tail->next = odd_dummy_head->next;
  return even_dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
