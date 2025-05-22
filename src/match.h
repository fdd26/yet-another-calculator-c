#pragma once

#include <stdbool.h>

#include "string_view.h"

bool matches_char(const char c, const StringView v);

bool matches_number(const StringView v);
