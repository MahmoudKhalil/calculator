#include "calculator_main_window.h"

struct _CalculatorMainWindow
{
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE (CalculatorMainWindow, calculator_main_window, GTK_TYPE_APPLICATION_WINDOW)

static void
calculator_main_window_numbers_btn_clicked (GtkWidget *widget, gpointer data)
{
    GtkEntry *numbers_entry = GTK_ENTRY (data);
    GtkButton *clicked_btn = GTK_BUTTON (widget);

    const gchar *clicked_btn_label = gtk_button_get_label (clicked_btn);
    const gchar *numbers_entry_text = gtk_entry_get_text (numbers_entry);

    const gchar *numbers_entry_new_text = g_strconcat (numbers_entry_text, clicked_btn_label);

    gtk_entry_set_text (numbers_entry, numbers_entry_new_text);
}

static void
calculator_main_window_operation_btn_clicked (GtkWidget *widget, gpointer data)
{
    g_print ("Operation clicked");
}

static void
calculator_main_window_negative_btn_clicked (GtkWidget *widget, gpointer data)
{
    g_print ("Negative clicked");
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
                                                
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (klass), calculator_main_window_numbers_btn_clicked);
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (klass), calculator_main_window_operation_btn_clicked);
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (klass), calculator_main_window_negative_btn_clicked);
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (klass), calculator_main_window_equal_btn_clicked);
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (klass), calculator_main_window_dot_btn_clicked);
}

CalculatorMainWindow *
calculator_main_window_new (CalculatorApplication *application)
{
    return g_object_new (CALCULATOR_TYPE_MAIN_WINDOW, "application", application, NULL);
}
