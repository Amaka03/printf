#include "main.h"

/**
 * handle_print - Prints an argument based on its type
 * @fmt: Formats the string for specified
 * @list: Lists all the arguments.
 * @ind: the printing buffer array.
 * @buffer: Buffer handling print.
 * @flags: Calculates all active flags
 * @width: gets the width.
 * @precision: printing Precision specification
 * @size: printing Size specifier
 * Return: 1 or 2.
 */

int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unkwn_lth = 0, print_char = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unkwn_lth += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unkwn_lth += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unkwn_lth += write(1, &fmt[*ind], 1);
		return (unkwn_lth);
	}
	return (print_char);
}
