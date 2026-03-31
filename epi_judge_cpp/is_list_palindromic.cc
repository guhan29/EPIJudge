#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseLL(shared_ptr<ListNode<int>>);

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
  shared_ptr<ListNode<int>> slow = L, fast = L;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  shared_ptr<ListNode<int>> first_half = L, second_half = ReverseLL(slow);
  while (first_half && second_half) {
    if (first_half->data != second_half->data) return false;
    first_half = first_half->next;
    second_half = second_half->next;
  }
  return true;
}

shared_ptr<ListNode<int>> ReverseLL(shared_ptr<ListNode<int>> head) {
  shared_ptr<ListNode<int>> curr = head, prev = nullptr;

  while (curr) {
    auto nextNode = curr->next;
    curr->next = prev;
    prev = curr;
    curr = nextNode;
  }
  return prev;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "is_list_palindromic.cc",
                         "is_list_palindromic.tsv", &IsLinkedListAPalindrome,
                         DefaultComparator{}, param_names);
}
