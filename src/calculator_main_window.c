#include "calculator_main_window.h"

struct _CalculatorMainWindow
{
    GtkApplicationWindow parent;

    GtkEntry *numbers_entry;

    CalculatorParser *parser;
};

G_DEFINE_TYPE (CalculatorMainWindow, calculator_main_window, GTK_TYPE_APPLICATION_WINDOW)

static void
calculator_main_window_display_input_to_numbers_entry (CalculatorMainWindow *self, GtkWidget *widget)
{
    CalculatorMainWindow *main_window = self;
    GtkButton *clicked_btn = GTK_BUTTON (widget);

    const gchar *clicked_btn_label = gtk_button_get_label (clicked_btn);
    const gchar *numbers_entry_text = gtk_entry_get_text (main_window->numbers_entry);

    const gchar *numbers_entry_new_text = g_strconcat (numbers_entry_text, clicked_btn_label);

    gtk_entry_set_text (main_window->numbers_entry, numbers_entry_new_text);
}

static void
calculator_main_window_digit_btn_clicked (GtkWidget *widget, gpointer data)
{
    CalculatorMainWindow *main_window = CALCULATOR_MAIN_WINDOW (data);
    const gchar *input = gtk_entry_get_text (main_window->numbers_entry);
    const gchar character = gtk_button_get_label (GTK_BUTTON (widget))[0];
    
    const gchar *result_exp = calculator_parser_insert_to_expression(main_window->parser, input, character);
    gtk_entry_set_text (main_window->numbers_entry, result_exp);
}

static void
calculator_main_window_operation_btn_clicked (GtkWidget *widget, gpointer data)
{
    CalculatorMainWindow *main_window = CALCULATOR_MAIN_WINDOW (data);
    const gchar *input = gtk_entry_get_text (main_window->numbers_entry);
    const gchar character = gtk_button_get_label (GTK_BUTTON (widget))[0];
    
    const gchar *result_exp = calculator_parser_insert_to_expression(main_window->parser, input, character);
    gtk_entry_set_text (main_window->numbers_entry, result_exp);
}

static void
calculator_main_window_negative_btn_clicked (GtkWidget *widget, gpointer data)
{

}

static void
calculator_main_window_equal_btn_clicked (GtkWidget *widget, gpointer data)
{

}

static void
calculator_main_window_dot_btn_clicked (GtkWidget *widget, gpointer data)
{
    CalculatorMainWindow *main_window = CALCULATOR_MAIN_WINDOW (data);
    const gchar *input = gtk_entry_get_text (main_window->numbers_entry);
    const gchar character = gtk_button_get_label (GTK_BUTTON (widget))[0];
    
    const gchar *result_exp = calculator_parser_insert_to_expression(main_window->parser, input, character);
    gtk_entry_set_text (main_window->numbers_entry, result_exp);
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
                                                
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (klass), calculator_main_window_digit_btn_clicked);
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
