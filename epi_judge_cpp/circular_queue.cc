#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

#include <vector>

using std::vector;
using std::rotate;
class Queue {
 private:
  const int scale_factor = 2;
  int head = 0;
  int tail = 0;
  vector<int> entries;
  int entries_count = 0;
 public:
  Queue(size_t capacity) {
    entries.resize(capacity);
  }

  void Enqueue(int x) {
    if (entries_count == entries.size()) {
      rotate(entries.begin(), entries.begin() + head, entries.end());
      head = 0;
      tail = entries_count;
      entries.resize(entries.size() * scale_factor);
    }
    entries[tail] = x;
    tail = (tail + 1) % entries.size();
    entries_count++;
  }
  int Dequeue() {
    if (entries_count == 0) return -1;
    entries_count--;
    int res = entries[head];
    head = (head + 1) % entries.size();
    return res;
  }
  int Size() const {
    return entries_count;
  }
};
struct QueueOp {
  enum class Operation { kConstruct, kDequeue, kEnqueue, kSize } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = Operation::kConstruct;
    } else if (op_string == "dequeue") {
      op = Operation::kDequeue;
    } else if (op_string == "enqueue") {
      op = Operation::kEnqueue;
    } else if (op_string == "size") {
      op = Operation::kSize;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }

  void execute(Queue& q) const {
    switch (op) {
      case Operation::kConstruct:
        // Hack to bypass deleted assign operator
        q.~Queue();
        new (&q) Queue(argument);
        break;
      case Operation::kDequeue: {
        int result = q.Dequeue();
        if (result != argument) {
          throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                            ", got " + std::to_string(result));
        }
      } break;
      case Operation::kEnqueue:
        q.Enqueue(argument);
        break;
      case Operation::kSize: {
        int s = q.Size();
        if (s != argument) {
          throw TestFailure("Size: expected " + std::to_string(argument) +
                            ", got " + std::to_string(s));
        }
      } break;
    }
  }
};

namespace test_framework {
template <>
struct SerializationTrait<QueueOp> : UserSerTrait<QueueOp, std::string, int> {};
}  // namespace test_framework

void QueueTester(const std::vector<QueueOp>& ops) {
  Queue q(0);
  for (auto& op : ops) {
    op.execute(q);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
