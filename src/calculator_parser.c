#include "calculator_parser.h"

struct _CalculatorParser
{
    GObject parent;

    gchar *postfix_expression;
};

G_DEFINE_TYPE (CalculatorParser, calculator_parser, G_TYPE_OBJECT);


static void
calculator_parser_parse_numbers (CalculatorParser *self)
{
    
}

static void
calculator_parser_parse_expression (CalculatorParser *self, const gchar *input)
{
    // if (input[0] == '\0')
    // {
    //     return;
    // }

    // if (self->postfix_expression != NULL)
    // {
    //     g_free (self->postfix_expression);
    // }
    
    // for (guint i = 0; input[i] != '\0'; i++)
    // {
    //     if (input[i] != '+' && input[i] != '*' && input[i] != '/')
    //     {
    //         self->postfix_expression = 
    //     }
    // }
}

static gboolean
calculator_parser_check_floating_point (CalculatorParser *self, const gchar *input)
{
    gint len = strlen (input);

    if (input[0] == '\0')
    {
        return TRUE;
    }

    if (input[len - 1] == '+' || input[len - 1] == '-' || input[len - 1] == '*' || input[len - 1] == '/')
    {
        return TRUE;
    }

    for (int i = len - 1; i > 0; i--)
    {
        if (input[i] == '.')
        {
            return FALSE;
        }
        else if (input[len - 1] == '+' || input[len - 1] == '-' || input[len - 1] == '*' || input[len - 1] == '/')
        {
            return TRUE;
        }
    }

    return TRUE;
}

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

const gchar *
calculator_parser_insert_to_expression (CalculatorParser *self, const gchar *input, const gchar character)
{
    gchar *result_exp;
    if (input[0] == '\0')
    {
        if (character == '+' || character == '*' || character == '/')
        {
            return "Invalid Expression !";
        }

        if (character == '.')
        {
            result_exp = g_strconcat ("0", ".", NULL);
            
            return (const gchar *) result_exp;
        }
    }
    else if (character == '+' || character == '*' || character == '/')
    {
        gchar input_last_char = input[strlen (input) - 1];

        if (input_last_char == '+' || input_last_char == '-' || input_last_char == '*' || input_last_char == '/')
        {
            result_exp = g_strdup (input);
            result_exp[strlen (result_exp) - 1] = character;
            
            return (const gchar *) result_exp;
        }
    }
    else if (character == '-')
    {
        gchar input_last_char = input[strlen (input) - 1];

        if (input_last_char == '+')
        {
            result_exp = g_strdup (input);
            result_exp[strlen (result_exp) - 1] = character;
            
            return (const gchar *) result_exp;
        }
    }
    else if (character == '0')
    {
        gchar input_last_char = input[strlen (input) - 1];

        if (input_last_char == '0' && (strlen (input) == 1 || input[strlen (input) - 2] == '+' 
            || input[strlen (input) - 2] == '-' || input[strlen (input) - 2] == '*'
            || input[strlen (input) - 2] == '/'))
        {
            return input;
        }
    }
    else if (character == '.')
    {
        if (calculator_parser_check_floating_point (self, input))
        {
            return (const gchar *) g_strconcat (input, ".", NULL);
        }
    }
    else
    {
        gchar input_last_char = input[strlen (input) - 1];

        if (input_last_char == '0' && (strlen (input) == 1 || input[strlen (input) - 2] == '+' 
            || input[strlen (input) - 2] == '-' || input[strlen (input) - 2] == '*'
            || input[strlen (input) - 2] == '/'))
        {
            result_exp = g_strdup (input);
            
            result_exp[strlen (result_exp) - 1] = character;

            return (const gchar *) result_exp;
        }
    }

    char tmp[2] = ".";
    tmp[0] = character;
    if (input[0] == '\0')
    {
        result_exp = g_strconcat (tmp, NULL);
    }
    else
    {
        result_exp = g_strconcat (input, tmp, NULL);
    }

    return (const gchar *) result_exp;
}

gboolean
calculator_parser_append_zero (CalculatorParser *self, const gchar *input)
{
    
}

gdouble
calculator_parser_evaluate_expression (CalculatorParser *self, const gchar *text)
{
    calculator_parser_parse_expression (self, text);
}