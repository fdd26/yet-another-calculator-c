
#define _GNU_SOURCE // for getline

#include <stdio.h>
#include <stdlib.h>

#include "string_view.h"
#include "tokenizer.h"

const char *eval(const char *in, const size_t in_len, char *out,
                 const size_t out_len) {
  int start = 0;
  int final_count = 0;

  for (size_t i = 0; i < in_len; i++) {
    const StringView sv = (StringView){in_len - i, &in[i]};

    int count = 0;
    for (size_t j = 0; j < sv.len; j++) {
      if (matches_number((StringView){j, sv.str_p})) {
        count = (int)j;
      }
    }
    if (count > final_count) {
      start = (int)i;
      final_count = count;
    }
  }

  if (final_count != 0) {
    snprintf(out, out_len, "%.*s is number", final_count, &in[start]);
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
