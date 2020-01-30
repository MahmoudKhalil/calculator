#include "calculator_parser.h"

struct _CalculatorParser
{
    GObject parent;

    gchar *postfix_expression;
    gchar *operators;
};

G_DEFINE_TYPE (CalculatorParser, calculator_parser, G_TYPE_OBJECT);


static void
calculator_parser_parse_numbers (CalculatorParser *self)
{
    
}

static void
calculator_parser_parse_expression (CalculatorParser *self, const gchar *input)
{
    if (input[0] == '\0')
    {
        return;
    }

    if (self->postfix_expression != NULL)
    {
        g_free (self->postfix_expression);
        self->postfix_expression = NULL;
    }

    if (self->operators != NULL)
    {
        g_free (self->operators);
        self->operators = NULL;
    }
    
    for (guint i = 0; input[i] != '\0'; i++)
    {
        g_printf ("Inside the loop\n");

        if (input[i] == '+' || input[i] == '*' || input[i] == '/')
        {
            self->postfix_expression = g_strconcat (self->postfix_expression, ",", NULL);

            char tmp[2] = ".";
            tmp[0] = input[i];
            if (self->operators == NULL)
            {
                self->operators = g_strconcat (tmp, NULL);
            }
            else
            {
                self->operators = g_strconcat (self->operators, ",", NULL);
                self->operators = g_strconcat (self->operators, tmp, NULL);
            }

            continue;
        }
        else if (input[i] == '-')
        {
            if (i != 0 && input[i - 1] != '+' && input[i - 1] != '-' && input[i - 1] != '*' && input[i - 1] != '/')
            {
                self->postfix_expression = g_strconcat (self->postfix_expression, ",", NULL);

                char tmp[2] = ".";
                tmp[0] = input[i];
                if (self->operators == NULL)
                {
                    self->operators = g_strconcat (tmp, NULL);
                }
                else
                {
                    self->operators = g_strconcat (self->operators, ",", NULL);
                    self->operators = g_strconcat (self->operators, tmp, NULL);
                }
                continue;
            }
        }

        char tmp[2] = ".";
        tmp[0] = input[i];

        if (self->postfix_expression == NULL)
        {
            self->postfix_expression = g_strconcat (tmp, NULL);
            continue;
        }

        self->postfix_expression = g_strconcat (self->postfix_expression, tmp, NULL);
    }

    g_printf ("Postfix Expression : %s\n", self->postfix_expression);
    g_printf ("operators : %s\n", self->operators);
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
            if (strlen (input) == 1)
            {
                return "Invalid Expression !";
            }

            result_exp = g_strdup (input);
            result_exp[strlen (result_exp) - 1] = character;
            
            return (const gchar *) result_exp;
        }
    }
    else if (character == '-')
    {
        gchar input_last_char = input[strlen (input) - 1];

        if (input_last_char == '+' || input_last_char == '-')
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
    else if (character == '=') {
        gchar last_char = input[strlen (input) - 1];
        if (last_char == '+' || last_char == '-' || last_char == '*' || last_char == '/')
        {
            return "Invalid Expression !";
        }
        else
        {
            return input;
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

const gchar *
calculator_parser_evaluate_expression (CalculatorParser *self, const gchar *text)
{
    if (g_strcmp0 (text, "Invalid Expression!") == 0)
    {
        return text;
    }

    calculator_parser_parse_expression (self, text);
    gchar **str_operands, **str_operators;
    // Should handle NULL
    if (self->postfix_expression != NULL)
    {
        str_operands = g_strsplit (self->postfix_expression, ",", 10);
    }
    else
    {
        return text;
    }

    if (self->operators != NULL)
    {
        str_operators = g_strsplit (self->operators, ",", 1);
    }
    else
    {
        return text;
    }

    gint operators_index = 0;
    gdouble result = g_ascii_strtod (str_operands[0], NULL);
    g_printf ("Number is : %lf\n", result);

    for (int i = 1; str_operands[i] != NULL; i++)
    {
        gdouble tmp = g_ascii_strtod (str_operands[i], NULL);

        if (g_strcmp0 (str_operators[operators_index], "+") == 0)
        {
            result = result + tmp;
        }
        else if (g_strcmp0 (str_operators[operators_index], "-") == 0)
        {
            result = result - tmp;
        }
        else if (g_strcmp0 (str_operators[operators_index], "*") == 0)
        {
            result = result * tmp;
        }
        else if (g_strcmp0 (str_operators[operators_index], "/") == 0)
        {
            result = result / tmp;
        }

        operators_index++;
    }

    gchar buffer[20];
    const gchar *str_result = g_ascii_dtostr (buffer, 20, result);

    g_printf ("Result : %s\n", str_result);
    return g_locale_to_utf8 (str_result, -1, NULL, NULL, NULL);
}