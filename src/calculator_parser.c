#include "calculator_parser.h"

struct _CalculatorParser
{
    GObject parent;

    GPtrArray *numbers_array;
    GPtrArray *operators_array;
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
calculator_parser_parse_numbers (CalculatorParser *self, const gchar *input)
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
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
        {
            g_ptr_array_add (self->numbers_array, number);

            number = g_strdup ("\0");
            continue;
        }

        gchar *tmp = g_strdup (".");
        tmp[0] = input[i];
        number = g_strconcat (number, tmp, NULL);
    }

    for (int i = 0; i < self->numbers_array->len; i++)
    {
        g_printf ("Number %d : %s\n", i, g_ptr_array_index (self->numbers_array, i));
    }
}

gboolean
calculator_parser_append_zero (CalculatorParser *self, const gchar *input)
{
    calculator_parser_parse_numbers (self, input);

    return TRUE;
}