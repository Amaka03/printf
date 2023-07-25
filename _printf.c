#include "main.h"

void print_buffer(char buffer[], int *bu_in);

/**
 * _printf - defined Printf function
 * @format: format specifiers for strings.
 * Return: Printed characters.
 */
int _printf(const char *format, ...)
{
	int i, print = 0, print_char = 0;
	int flag, wdth, preci, size, bu_in = 0;
	va_list lt;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(lt, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[bu_in++] = format[i];
			if (bu_in == BUFF_SIZE)
				print_buffer(buffer, &bu_in);
			/* write(1, &format[i], 1);*/
			print_char++;
		}
		else
		{
			print_buffer(buffer, &bu_in);
			flag = get_flags(format, &i);
			wdth = get_width(format, &i, lt);
			preci = get_precision(format, &i, lt);
			size = get_size(format, &i);
			++i;
			print = handle_print(format, &i, lt, buffer,
				flag, wdth, preci, size);
			if (print == -1)
				return (-1);
			print_char += print;
		}
	}

	print_buffer(buffer, &bu_in);

	va_end(lt);

	return (print_char);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @bu_in: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *bu_in)
{
	if (*bu_in > 0)
		write(1, &buffer[0], *bu_in);

	*bu_in = 0;
}
