#include "calculator_main_window.h"

struct _CalculatorMainWindow
{
    GtkApplicationWindow parent;

    GtkEntry *numbers_entry;

    CalculatorParser *parser;
};

G_DEFINE_TYPE (CalculatorMainWindow, calculator_main_window, GTK_TYPE_APPLICATION_WINDOW)

static void
calculator_main_window_adding_input_to_numbers_entry (CalculatorMainWindow *self, GtkWidget *widget)
{
    CalculatorMainWindow *main_window = self;
    GtkButton *clicked_btn = GTK_BUTTON (widget);

    const gchar *clicked_btn_label = gtk_button_get_label (clicked_btn);
    const gchar *numbers_entry_text = gtk_entry_get_text (main_window->numbers_entry);

    const gchar *numbers_entry_new_text = g_strconcat (numbers_entry_text, clicked_btn_label);

    gtk_entry_set_text (main_window->numbers_entry, numbers_entry_new_text);
}

static void
calculator_main_window_numbers_btn_clicked (GtkWidget *widget, gpointer data)
{
    CalculatorMainWindow *main_window = CALCULATOR_MAIN_WINDOW (data);

    const gchar *clicked_btn_label = gtk_button_get_label (GTK_BUTTON (widget));

    if (g_strcmp0 (clicked_btn_label, "0") == 0)
    {
        if (! calculator_parser_append_zero (main_window->parser, gtk_entry_get_text (main_window->numbers_entry)))
        {
            return;
        }
    }
    
    calculator_main_window_adding_input_to_numbers_entry (main_window, widget);
}

static void
calculator_main_window_operation_btn_clicked (GtkWidget *widget, gpointer data)
{
    CalculatorMainWindow *main_window = CALCULATOR_MAIN_WINDOW (data);
    
    calculator_main_window_adding_input_to_numbers_entry (main_window, widget);
}

static void
calculator_main_window_negative_btn_clicked (GtkWidget *widget, gpointer data)
{
    CalculatorMainWindow *main_window = CALCULATOR_MAIN_WINDOW (data);

    // gtk_entry_set_text (main_window->numbers_entry, 
                        // calculator_parser_insert_negative (main_window->parser, gtk_entry_get_text (main_window->numbers_entry)));
}

static void
calculator_main_window_equal_btn_clicked (GtkWidget *widget, gpointer data)
{
    CalculatorMainWindow *main_window = CALCULATOR_MAIN_WINDOW (data);
    
    calculator_main_window_adding_input_to_numbers_entry (main_window, widget);

    calculator_parser_calculate_expression (main_window->parser, gtk_entry_get_text (main_window->numbers_entry));
}

static void
calculator_main_window_dot_btn_clicked (GtkWidget *widget, gpointer data)
{
    CalculatorMainWindow *main_window = CALCULATOR_MAIN_WINDOW (data);
    
    calculator_main_window_adding_input_to_numbers_entry (main_window, widget);
}

static void
calculator_main_window_init (CalculatorMainWindow *instance)
{
    gtk_widget_init_template (GTK_WIDGET (instance));
}

static void
calculator_main_window_class_init (CalculatorMainWindowClass *klass)
{
    gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (klass),
                                                    "/calculator/application/main_window.ui");

    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (klass), CalculatorMainWindow, numbers_entry);
                                                
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (klass), calculator_main_window_numbers_btn_clicked);
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (klass), calculator_main_window_operation_btn_clicked);
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (klass), calculator_main_window_negative_btn_clicked);
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (klass), calculator_main_window_equal_btn_clicked);
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (klass), calculator_main_window_dot_btn_clicked);
}

CalculatorMainWindow *
calculator_main_window_new (CalculatorApplication *application, CalculatorParser *parser)
{
    CalculatorMainWindow *calculator_main_window = g_object_new (CALCULATOR_TYPE_MAIN_WINDOW, "application", application, NULL);
    calculator_main_window->parser = parser;

    return calculator_main_window;
}
