#pragma once

#include <gtk/gtk.h>

#include "calculator_application.h"
#include "calculator_parser.h"

G_BEGIN_DECLS

#define CALCULATOR_TYPE_MAIN_WINDOW (calculator_main_window_get_type ())

G_DECLARE_FINAL_TYPE (CalculatorMainWindow, calculator_main_window, CALCULATOR, MAIN_WINDOW, GtkApplicationWindow)

CalculatorMainWindow *
calculator_main_window_new (CalculatorApplication *application, CalculatorParser *parser);

G_END_DECLS
