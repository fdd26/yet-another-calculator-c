
#include "tokenizer.h"

#include <ctype.h>

bool matches_number(const StringView sv) {
  // simulating regex:
  // [0-9]+

  if (sv.len == 0) {
    return false;
  }
  bool ret = true;
  for (size_t i = 0; i < sv.len; i++) {
    const char c = sv.str_p[i];
    ret &= isdigit(c) != 0;
  }
  return ret;
}
