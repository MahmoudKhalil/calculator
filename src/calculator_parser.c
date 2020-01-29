#include "calculator_parser.h"

struct _CalculatorParser
{
    GObject parent;

    GPtrArray *numbers_array;
    GPtrArray *operators_array;

    GArray *numbers;
};

G_DEFINE_TYPE (CalculatorParser, calculator_parser, G_TYPE_OBJECT);

static void
calculator_parser_init (CalculatorParser *instance)
{

}

static void
calculator_parser_class_init (CalculatorParserClass *klass)
{

}

CalculatorParser *
calculator_parser_new (void)
{
    return g_object_new (CALCULATOR_TYPE_PARSER, NULL);
}

static void
calculator_parser_parse_numbers (CalculatorParser *self)
{
    if (self->numbers != NULL)
    {
        g_array_free (self->numbers, TRUE);
    }

    self->numbers = g_array_new (FALSE, FALSE, sizeof (gdouble));

    for (int i = 0; i < self->numbers_array->len; i++)
    {
        gdouble number;
        sscanf (g_ptr_array_index (self->numbers_array, i), "%lf", &number);

        g_printf ("Number is : %lf\n", number);

        g_array_append_val (self->numbers, number);
    }

    for (int i = 0; i < self->numbers->len; i++)
    {
        g_printf ("gint number is : %lf\n", g_array_index (self->numbers, gdouble, i));
    }
}

static void
calculator_parser_parse_expression (CalculatorParser *self, const gchar *input)
{
    if (input[0] == '\0')
    {
        return;
    }

    if (self->numbers_array != NULL)
    {
        g_ptr_array_free (self->numbers_array, TRUE);
    }

    self->numbers_array = g_ptr_array_new ();

    gchar *number = g_strdup ("\0");
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == '+' || input[i] == '*' || input[i] == '/' || input[i] == '=')
        {
            g_ptr_array_add (self->numbers_array, number);

            number = g_strdup ("\0");
            continue;
        }
        else if (input[i] == '-')
        {
            if (i != 0 && (input[i - 1] != '+' || input[i - 1] != '*' || input[i - 1] != '/'))
            {
                g_ptr_array_add (self->numbers_array, number);

                number = g_strdup ("\0");
                continue;
            }
        }

        gchar *tmp = g_strdup (".");
        tmp[0] = input[i];
        number = g_strconcat (number, tmp, NULL);
    }

    calculator_parser_parse_numbers (self);
}

gboolean
calculator_parser_append_zero (CalculatorParser *self, const gchar *input)
{
    return TRUE;
}

gchar *
calculator_parser_insert_negative (CalculatorParser *self, const gchar *text)
{
    // calculator_parser_parse_expression (self, text);

    // gchar *last_number = g_ptr_array_index (self->numbers_array, self->numbers_array->len - 1);
    // g_printf ("last_number %s\n", last_number);

    // if (last_number[0] == '-')
    // {
    //     last_number = g_strdup (last_number + 1);
    //     g_printf ("last_number %s\n", last_number);
    // } 
    // else 
    // {
    //     last_number = g_strconcat("-", last_number);
    //     g_printf ("last_number %s\n", last_number);
    // }

    // return last_number;
}

void
calculator_parser_calculate_expression (CalculatorParser *self, const gchar *text)
{
    calculator_parser_parse_expression (self, text);
}