#include <algorithm>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

bool IsValid(const string&);

vector<string> GetValidIpAddress(const string& s) {
  vector<string> res;
  int n = s.size();
  for (int i = 1; i < 4 && i < n; i++) {
    const string first = s.substr(0, i);
    if (IsValid(first)) {
      for (int j = 1; j < 4 && i + j < n; j++) {
        const string second = s.substr(i, j);
        if (IsValid(second)) {
          for (int k = 1; k < 4 && i + j + k < n; k++) {
            const string third = s.substr(i + j, k);
            const string fourth = s.substr(i + j + k);
            if (IsValid(third) && IsValid(fourth)) {
              const string addr = first + "." + second + "." + third + "." + fourth;
              res.push_back(addr);
            }
          }
        }
      }
    }
  }
  return res;
}

bool IsValid(const string& s) {
  int n = s.size();
  if (n > 3) return false;
  if (s[0] == '0' && n > 1) return false;
  int num = stoi(s);
  return num >= 0 && num <= 255;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "valid_ip_addresses.cc",
                         "valid_ip_addresses.tsv", &GetValidIpAddress,
                         UnorderedComparator{}, param_names);
}
