#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TokenType {
	TOKEN_LPAREN  = 0,
	TOKEN_RPAREN  = 1,
	TOKEN_PLUS    = 2,
	TOKEN_MINUS   = 3,
	TOKEN_TIMES   = 4,
	TOKEN_DIVIDES = 5,
	TOKEN_NUM     = 6,
	TOKEN_LENGTH  = 7
};

static char* TOKENS[] = {
	"TOKEN_LPAREN",
	"TOKEN_RPAREN",
	"TOKEN_PLUS",
	"TOKEN_MINUS",
	"TOKEN_TIMES",
	"TOKEN_DIVIDES",
	"TOKEN_NUM",
	"TOKEN_LENGTH",
	NULL
};

enum TokenizerErrorType {
	TOKEN_ERROR_NONE       = 0,
	TOKEN_ERROR_UNEXPECTED = 1,
	TOKEN_ERROR_EOF        = 2,
	TOKEN_ERROR_LENGTH     = 3
};

static const char* TOKENIZER_ERROR_TYPE_NAME[] = {
	"TOKEN_ERROR_NONE",
	"TOKEN_ERROR_UNEXPECTED",
	"TOKEN_ERROR_EOF",
	"TOKEN_ERROR_LENGTH",
	NULL
};

struct SingleCharTokenEntry {
	char c;
	enum TokenType type;
};

static const struct SingleCharTokenEntry ALL_ENTRIES[] = {
	{'(', TOKEN_LPAREN},
	{')', TOKEN_RPAREN},
	{'+', TOKEN_PLUS},
	{'-', TOKEN_MINUS},
	{'*', TOKEN_TIMES},
	{'/', TOKEN_DIVIDES},
	{'0', TOKEN_NUM},
	{'1', TOKEN_NUM},
	{'2', TOKEN_NUM},
	{'3', TOKEN_NUM},
	{'4', TOKEN_NUM},
	{'5', TOKEN_NUM},
	{'6', TOKEN_NUM},
	{'7', TOKEN_NUM},
	{'8', TOKEN_NUM},
	{'9', TOKEN_NUM},
	{ 0, TOKEN_LENGTH }
};

/**
 * Convert array list into a lookup table
 */
static struct SingleCharTokenEntry MAP_ENTRY[257] = { 0 };

/**
 * Fill up the lookup table
 */
static void fill_map_entry()
{
	for(size_t i = 0; i < 17; ++i)
	{
		if (ALL_ENTRIES[i].c == 0) { break; }
		const char            ch   = ALL_ENTRIES[i].c;
		const enum TokenType  type = ALL_ENTRIES[i].type;

		MAP_ENTRY[ (const unsigned int) ch ] = ALL_ENTRIES[i];
	}
}

static struct SingleCharTokenEntry getTokenEntry(size_t i)
{
	// OOB protection
	if (i <= 0 || i > 255) { i = 0; }

	// Initialize if that was not done yet...
	if (ALL_ENTRIES['0'].c != '0')
	{
		fill_map_entry();
	}

	return ALL_ENTRIES[i];
}

int main()
{
	printf("working\n");

	//fill_map_entry();

	for(size_t i = 0; i < 256; ++i)
	{
		const unsigned char        ch0   = (const unsigned char) i;
		const SingleCharTokenEntry entry = getTokenEntry(i); //MAP_ENTRY[i];
		const const char           ch    = entry.c;
		const enum TokenType       type  = entry.type;

		printf("[%d][%x][%c][%x][%c][%d][%d]\n", i, ch0, (ch0 <= 32 ? ' ' : ch0), ch, (ch <= 32 ? ' ' : ch), ch, type);
	}

	printf("done\n");
	return 0;
}
