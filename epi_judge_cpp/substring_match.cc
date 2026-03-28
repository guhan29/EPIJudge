#include <string>

#include "test_framework/generic_test.h"
using std::string;

// Returns the index of the first character of the substring if found, -1
// otherwise.
int RabinKarp(const string &t, const string &s) {
  int t_len = t.size(), s_len = s.size();
  if (t_len < s_len) return -1;

  const int BASE = 26;
  int t_hash = 0, s_hash = 0;
  int power_s = 1;

  for (int i = 0; i < s_len; i++) {
    power_s = i ? power_s * BASE : 1;
    t_hash = t_hash * BASE + t[i];
    s_hash = s_hash * BASE + s[i];
  }
  for (int i = s_len; i <= t_len; i++) {
    if (t_hash == s_hash && t.compare(i - s_len, s_len, s) == 0) {
      return i - s_len;
    }
    t_hash -= t[i - s_len] * power_s;
    t_hash = t_hash * BASE + t[i];
  }
  return -1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"t", "s"};
  return GenericTestMain(args, "substring_match.cc", "substring_match.tsv",
                         &RabinKarp, DefaultComparator{}, param_names);
}
