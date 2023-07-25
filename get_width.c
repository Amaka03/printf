#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formats the string for specified
 * @i: List of all the formats to be printed.
 * @list: list of all arguments.
 * Return: specified integer.
 */

int get_width(const char *format, int *i, va_list list)
{
	int c_i;
	int width = 0;

	for (c_i = *i + 1; format[c_i] != '\0'; c_i++)
	{
		if (is_digit(format[c_i]))
		{
			width *= 10;
			width += format[c_i] - '0';
		}
		else if (format[c_i] == '*')
		{
			c_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = c_i - 1;

	return (width);
}
