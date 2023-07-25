#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a single character to the buffer.
 * @types: va_list containing the character to be printed.
 * @buffer: the buffer spicifier array to handle print.
 * @flags:  the calculates active flags
 * @width: field width to be printed
 * @precision:  Precision specification for printing.
 * @size:  the size specifier for printing.
 * Return: chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char k = va_arg(types, int);

	return (handle_write_char(k, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string to the buffer.
 * @types: va_list containing the string to be printed.
 * @buffer: the buffer specifier array to handle print.
 * @flags:  the calculates specifier for active flags.
 * @width: field width to be printed.
 * @precision: the precision specification for printing.
 * @size: the size specifier for printing.
 * Return: the number of characters printed.
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int lent = 0, i;
	char *sttr = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (sttr == NULL)
	{
		sttr = "(null)";
		if (precision >= 6)
			sttr = "      ";
	}

	while (sttr[lent] != '\0')
		lent++;

	if (precision >= 0 && precision < lent)
		lent = precision;

	if (width > lent)
	{
		if (flags & F_MINUS)
		{
			write(1, &sttr[0], lent);
			for (i = width - lent; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - lent; i > 0; i--)
				write(1, " ", 1);
			write(1, &sttr[0], lent);
			return (width);
		}
	}

	return (write(1, sttr, lent));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent to the buffer
 * @types: va_list containing the string to be printed.
 * @buffer: the buffer specifier for array to handle print
 * @flags:  the calculates specifierfor active flags
 * @width: get width.
 * @precision: the precision specification  for printing.
 * @size: the size specifier for printing.
 * Return: the umber specifier of characters printed.
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/************************* PRINT INT *************************/
/**
 * print_int - the print int to the buffer
 * @types: va_list containing the string to be printed.
 * @buffer: the buffer specifier for array to handle print
 * @flags:  the calculates specifier for active flags
 * @width: field width to be printed.
 * @precision: the precision specification for printing.
 * @size: the size specifier for printing.
 * Return: the number of characters printed.
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int nn = va_arg(types, long int);
	unsigned long int nm;

	nn = convert_size_number(nn, size);

	if (nn == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	nm = (unsigned long int)nn;

	if (nn < 0)
	{
		nm = (unsigned long int)((-1) * nn);
		is_negative = 1;
	}

	while (nm > 0)
	{
		buffer[i--] = (nm % 10) + '0';
		nm /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}
/************************* PRINT BINARY *************************/
/**
 * print_binary - the prints an unsigned number for buffer.
 * @types: va_list containing the string to be printed.
 * @buffer: the buffer specifier for array to handle print.
 * @flags:  the calculates active flags.
 * @width: field width to be printed.
 * @precision: the precision specification.
 * @size: the size specifier for printing.
 * Return: the numbers of characters printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int nnn, mm, i, sm;
	unsigned int a[32];
	int cnt;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	nnn = va_arg(types, unsigned int);
	mm = 2147483648;
	a[0] = nnn / mm;
	for (i = 1; i < 32; i++)
	{
		mm /= 2;
		a[i] = (nnn / mm) % 2;
	}
	for (i = 0, sm = 0, cnt = 0; i < 32; i++)
	{
		sm += a[i];
		if (sm || i == 31)
		{
			char l = '0' + a[i];

			write(1, &l, 1);
			cnt++;
		}
	}
	return (cnt);
}
