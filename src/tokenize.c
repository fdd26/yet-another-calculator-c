
#include "tokenize.h"

void sc_tokenizer_init(struct SingleCharTokenizer *self,
                       const size_t num_entries,
                       const struct SingleCharTokenEntry *entries,
                       const int invalid_entry_value) {
  for (int i = CHAR_MIN; i <= CHAR_MAX; i++) {
    self->table[i - CHAR_MIN] = invalid_entry_value;
  }
  for (size_t i = 0; i < num_entries; i++) {
    self->table[entries[i].c - CHAR_MIN] = entries[i].type;
  }
  self->invalid_entry_value = invalid_entry_value;
}

enum TokenizerErrorType sc_try_tokenize(struct SingleCharTokenizer *self,
                                        const char c, int *out) {
  if (self->table[c - CHAR_MIN] != self->invalid_entry_value) {
    *out = self->table[c - CHAR_MIN];
    return TOKEN_ERROR_NONE;
  }
  return TOKEN_ERROR_UNEXPECTED;
}
