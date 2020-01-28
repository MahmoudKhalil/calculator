#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define CALCULATOR_TYPE_APPLICATION (calculator_application_get_type ())

G_DECLARE_FINAL_TYPE (CalculatorApplication, calculator_application, CALCULATOR, APPLICATION, GtkApplication)

CalculatorApplication *
calculator_application_new (void);

G_END_DECLS
