#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> AddTwoNumbers(shared_ptr<ListNode<int>> L1,
                                        shared_ptr<ListNode<int>> L2) {
  int carry = 0;
  auto head = make_shared<ListNode<int>>(), it = head;
  while (L1 || L2 || carry) {
    int sum = (L1 ? L1->data : 0) + (L2 ? L2->data : 0) + carry;
    L1 = L1 ? L1->next : nullptr;
    L2 = L2 ? L2->next : nullptr;
    it->next = make_shared<ListNode<int>>(sum % 10);
    it = it->next;
    carry = sum / 10;
  }
  return head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "int_as_list_add.cc", "int_as_list_add.tsv",
                         &AddTwoNumbers, DefaultComparator{}, param_names);
}
