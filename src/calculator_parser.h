#pragma once

#include <stdio.h>
#include <string.h>

#include <glib.h>
#include <glib/gprintf.h>
#include <gmodule.h>

#include "calculator_application.h"

G_BEGIN_DECLS

#define CALCULATOR_TYPE_PARSER (calculator_parser_get_type ())

G_DECLARE_FINAL_TYPE (CalculatorParser, calculator_parser, CALCULATOR, PARSER, GObject)

CalculatorParser *
calculator_parser_new (void);

const gchar *
calculator_parser_insert_to_expression (CalculatorParser *self, const gchar *input, const gchar character);

const gchar *
calculator_parser_evaluate_expression (CalculatorParser *self, const gchar *text);

G_END_DECLS