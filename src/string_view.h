#pragma once

#include <assert.h>
#include <stddef.h>

struct StringView {
  size_t len;
  const char *str_p;
};

static inline void sv_consume_char(struct StringView *sv)
{
  assert(sv->len != 0);
  sv->len = sv->len - 1;
  sv->str_p = &sv->str_p[1];
}

static inline const char *
sv_peek_char(struct StringView *sv, const size_t i)
{
  if (i + 1 < sv->len) {
    return &sv->str_p[i + 1];
  }
  return NULL;
}
