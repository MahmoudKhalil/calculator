#pragma once

#include <glib.h>

#include "calculator_application.h"

G_BEGIN_DECLS

#define CALCULATOR_TYPE_PARSER (calculator_parser_get_type ())

G_DEFINE_FINAL_TYPE (CalculatorParser, calculator_parser, CALCULATOR, PARSER, GObject)

CalculatorParser *
calculator_parser_new (gchar *text);

G_END_DECLS