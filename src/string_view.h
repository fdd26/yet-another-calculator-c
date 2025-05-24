#pragma once

#include <assert.h>
#include <stddef.h>

struct StringView {
  size_t len;
  const char *str_p;
};
