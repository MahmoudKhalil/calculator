#include "calculator_application.h"
#include "calculator_main_window.h"
#include "calculator_parser.h"

struct _CalculatorApplication
{
    GtkApplication parent;
};

G_DEFINE_TYPE (CalculatorApplication, calculator_application, GTK_TYPE_APPLICATION)

static void
calculator_application_activate (GApplication *application)
{
    CalculatorApplication *calculator_application = CALCULATOR_APPLICATION (application);

    CalculatorParser *parser = calculator_parser_new ();

    CalculatorMainWindow *main_window = calculator_main_window_new (calculator_application, parser);
    
    gtk_window_present (GTK_WINDOW (main_window));
}

static void
calculator_application_init (CalculatorApplication *instance)
{
}

static void
calculator_application_class_init (CalculatorApplicationClass *klass)
{
    G_APPLICATION_CLASS (klass)->activate = calculator_application_activate;
}

CalculatorApplication *
calculator_application_new (void)
{
    return g_object_new (CALCULATOR_TYPE_APPLICATION, "application-id", "org.gtk.calculator", NULL);
}
