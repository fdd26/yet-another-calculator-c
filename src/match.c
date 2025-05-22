
#include "match.h"

#include <ctype.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))

bool matches_char(const char c, const StringView v) {
  if (v.len != 1) {
    return false;
  }
  return c == v.str_p[0];
}

bool matches_number(const StringView v) {
  // simulating regex:
  // [0-9]+

  if (v.len == 0) {
    return false;
  }
  bool ret = true;
  for (size_t i = 0; i < v.len; i++) {
    ret &= isdigit(v.str_p[i]) != 0;
  }
  return ret;
}
