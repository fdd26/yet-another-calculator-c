
#define _GNU_SOURCE // for getline

#include <stdio.h>
#include <stdlib.h>

#include "match.h"
#include "string_view.h"

enum Lexeme {
  LEX_DEFAULT = 0,
  LEX_NUM,
  LEX_PLUS,
  LEX_TIMES,
};

const char *eval(const char *in, const size_t in_len, char *out,
                 const size_t out_len) {
  enum Lexeme final_tok = LEX_DEFAULT;
  int start = 0;
  int final_count = 0;

  for (size_t i = 0; i < in_len; i++) {
    const StringView sv = (StringView){in_len - i, &in[i]};

    enum Lexeme tok = LEX_DEFAULT;
    int count = 0;
    for (size_t j = 0; j < sv.len; j++) {
      if (matches_number((StringView){j, sv.str_p})) {
        count = (int)j;
        tok = LEX_NUM;
      } else if (matches_char('+', (StringView){j, sv.str_p})) {
        count = (int)j;
        tok = LEX_PLUS;
      } else if (matches_char('*', (StringView){j, sv.str_p})) {
        count = (int)j;
        tok = LEX_TIMES;
      }
    }
    if (count > final_count) {
      start = (int)i;
      final_count = count;
      final_tok = tok;
    }
    if (sv.str_p[0] != ' ') {
      break;
    }
  }

  if (final_count != 0) {
    switch (final_tok) {
    case LEX_NUM:
      snprintf(out, out_len, "%.*s is number", final_count, &in[start]);
      break;
    case LEX_PLUS:
      snprintf(out, out_len, "%.*s is plus operator", final_count, &in[start]);
      break;
    case LEX_TIMES:
      snprintf(out, out_len, "%.*s is times operator", final_count, &in[start]);
      break;
    case LEX_DEFAULT:
      snprintf(out, out_len, "default token for some reason");
      break;
    }
  } else {
    snprintf(out, out_len, "unknown");
  }

  return out;
}

int main(void) {
  char *line_p = NULL;
  size_t n = 0;
  ssize_t len = 0;

  char out[512];

  printf("Press Ctrl+d to exit.\n\n");
  printf("> ");

  while (0 < (len = getline(&line_p, &n, stdin))) {
    printf("%s\n", eval(line_p, (size_t)len, out, sizeof(out)));
    printf("> ");
  }
  free(line_p);
  return 0;
}
