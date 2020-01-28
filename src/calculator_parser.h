#pragma once

#include <glib.h>
#include <glib/gprintf.h>
#include <gmodule.h>

#include <string.h>

#include "calculator_application.h"

G_BEGIN_DECLS

#define CALCULATOR_TYPE_PARSER (calculator_parser_get_type ())

G_DECLARE_FINAL_TYPE (CalculatorParser, calculator_parser, CALCULATOR, PARSER, GObject)

CalculatorParser *
calculator_parser_new (void);

gboolean
calculator_parser_append_zero (CalculatorParser *self, const gchar *input);

G_END_DECLS