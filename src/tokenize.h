#pragma once

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#include "string_view.h"

enum TokenizerErrorType {
  TOKEN_ERROR_NONE = 0,
  TOKEN_ERROR_UNEXPECTED,
  TOKEN_ERROR_EOF,
  // TOKEN_ERROR_CUSTOM,
};

struct SingleCharTokenEntry {
  char c;
  int type;
};

struct SingleCharTokenizer {
  int table[CHAR_MAX - CHAR_MIN + 2];
  int invalid_entry_value;
};

void sc_tokenizer_init(
    struct SingleCharTokenizer *self,
    const size_t num_entries,
    const struct SingleCharTokenEntry *entries,
    const int invalid_entry_value);

enum TokenizerErrorType sc_try_tokenize(
    struct SingleCharTokenizer *self, //
    const char c,
    int *out);

// struct MultiCharTokenEntry {
//   const char *str;
//   const int type;
// };
