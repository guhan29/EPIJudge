#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;
using std::to_string;
string Decoding(const string &s) {
  string decoded;
  int count = 0;
  for (const char& ch : s) {
    if (isdigit(ch)) {
      count = count * 10 + (ch - '0');
    } else {
      string str(count, ch);
      decoded += str;
      count = 0;
    }
  }
  return decoded;
}
string Encoding(const string &s) {
  string encoded = "";
  int count = 1;
  for (int i = 1; i <= s.size(); i++) {
    if (i == s.size() || s[i - 1] != s[i]) {
      encoded += to_string(count) + s[i - 1];
      count = 1;
    } else {
      count++;
    }
  }
  return encoded;
}
void RleTester(const string &encoded, const string &decoded) {
  if (Decoding(encoded) != decoded) {
    throw TestFailure("Decoding failed");
  }
  if (Encoding(decoded) != encoded) {
    throw TestFailure("Encoding failed");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"encoded", "decoded"};
  return GenericTestMain(args, "run_length_compression.cc",
                         "run_length_compression.tsv", &RleTester,
                         DefaultComparator{}, param_names);
}
