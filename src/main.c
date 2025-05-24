
#include <ctype.h>
#define _GNU_SOURCE // for getline

#include <stdio.h>
#include <stdlib.h>

#include "string_view.h"
#include "tokenize.h"

#define ARRAY_SIZE(a) sizeof(a) / sizeof(*a)

static const int INVALID_TOKEN_TYPE = -1;

enum TokenType {
  TOKEN_LPAREN = 0,
  TOKEN_RPAREN,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_TIMES,
  TOKEN_DIVIDES,
  TOKEN_NUM,
};

static const struct SingleCharTokenEntry SYMBOL_ENTRIES[] = {
    {'(', TOKEN_LPAREN}, {')', TOKEN_RPAREN}, {'+', TOKEN_PLUS},
    {'-', TOKEN_MINUS},  {'*', TOKEN_TIMES},  {'/', TOKEN_DIVIDES},
};

static const struct SingleCharTokenEntry NUM_ENTRIES[] = {
    {'0', TOKEN_NUM}, {'1', TOKEN_NUM}, {'2', TOKEN_NUM}, {'3', TOKEN_NUM},
    {'4', TOKEN_NUM}, {'5', TOKEN_NUM}, {'6', TOKEN_NUM}, {'7', TOKEN_NUM},
    {'8', TOKEN_NUM}, {'9', TOKEN_NUM}};

struct TokenizerContext {
  struct SingleCharTokenizer symbol_tokenizer;
  struct SingleCharTokenizer num_tokenizer;
};

struct TokenizerContext create_static_tokenizer(void) {
  struct TokenizerContext res = {0};
  sc_tokenizer_init(&res.symbol_tokenizer, //
                    ARRAY_SIZE(SYMBOL_ENTRIES),
                    SYMBOL_ENTRIES, //
                    INVALID_TOKEN_TYPE);
  sc_tokenizer_init(&res.num_tokenizer, //
                    ARRAY_SIZE(NUM_ENTRIES),
                    NUM_ENTRIES, //
                    INVALID_TOKEN_TYPE);
  return res;
}

enum TokenizerErrorType try_tokenize(struct TokenizerContext *context,
                                     struct StringView *sv,
                                     enum TokenType *out) {
  while (sv->len > 0 && isspace(sv->str_p[0])) {
    sv_consume_char(sv);
  }
  if (sv->len == 0) {
    return TOKEN_ERROR_EOF;
  }
  int token_type = INVALID_TOKEN_TYPE;

  if (sc_try_tokenize(&context->symbol_tokenizer, sv->str_p[0], &token_type) ==
      TOKEN_ERROR_NONE) {
    *out = (enum TokenType)token_type;
    sv_consume_char(sv);
    return TOKEN_ERROR_NONE;
  }

  if (sc_try_tokenize(&context->num_tokenizer, sv->str_p[0], &token_type) ==
      TOKEN_ERROR_NONE) {
    *out = (enum TokenType)token_type;
    sv_consume_char(sv);

    while (sv->len > 0 &&
           (sc_try_tokenize(&context->num_tokenizer, sv->str_p[0],
                            &token_type) == TOKEN_ERROR_NONE)) {
      *out = (enum TokenType)token_type;
      sv_consume_char(sv);
    }
    return TOKEN_ERROR_NONE;
  }

  return TOKEN_ERROR_UNEXPECTED;
}

int main(void) {
  char *line_p = NULL;
  size_t n = 0;
  ssize_t len = 0;

  struct TokenizerContext tokenizer =
      create_static_tokenizer(); // this can be changed later on

  printf("Press Ctrl+d to exit.\n\n");
  printf("> ");

  while (0 < (len = getline(&line_p, &n, stdin))) {
    struct StringView sv = {.len = (size_t)len, .str_p = line_p};
    enum TokenizerErrorType e = TOKEN_ERROR_NONE;
    enum TokenType t = (enum TokenType)INVALID_TOKEN_TYPE;

    while ((e = try_tokenize(&tokenizer, &sv, &t)) != TOKEN_ERROR_EOF) {
      if (e == TOKEN_ERROR_UNEXPECTED) {
        printf("unexpected: %c", sv.str_p[0]);
        break;
      }
      switch (t) {
      case TOKEN_LPAREN:
        printf("LPAREN ");
        break;
      case TOKEN_RPAREN:
        printf("RPAREN ");
        break;
      case TOKEN_PLUS:
        printf("PLUS ");
        break;
      case TOKEN_MINUS:
        printf("MINUS ");
        break;
      case TOKEN_TIMES:
        printf("TIMES ");
        break;
      case TOKEN_DIVIDES:
        printf("DIVIDES ");
        break;
      case TOKEN_NUM:
        printf("NUM ");
        break;
      }
    }
    printf("\n> ");
  }
  free(line_p);
  return 0;
}
