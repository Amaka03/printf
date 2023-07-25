#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - the prints value of a pointer variable to the buffer.
 * @types: va_list containing the string to be printed.
 * @buffer: the buffer specifier for array to handle print.
 * @flags:  the calculates specifier for active flags.
 * @width: field width to be printed.
 * @precision: the precision specificatier for printing.
 * @size: the size specifier for printing.
 * Return: the number of characters printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extr_c = 0, pdd = ' ';
	int iind = BUFF_SIZE - 2, lent = 2, pdd_start = 1;
	unsigned long nm_addrs;
	char map_to[] = "0123456789abcdef";
	void *adddrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (adddrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	nm_addrs = (unsigned long)adddrs;

	while (nm_addrs > 0)
	{
		buffer[iind--] = map_to[nm_addrs % 16];
		nm_addrs /= 16;
		lent++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pdd = '0';
	if (flags & F_PLUS)
		extr_c = '+', lent++;
	else if (flags & F_SPACE)
		extr_c = ' ', lent++;

	iind++;

	return (write_pointer(buffer, iind, lent,
		width, flags, pdd, extr_c, pdd_start));
}
/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - prints ascii in hexa of non printable characters
 * @types: va_list containing the string to be printed.
 * @buffer: the buffer specifier for array to handle print
 * @flags:  the calculates specifier for active flags.
 * @width: field width to be printed.
 * @precision: the precision specificatier for printing.
 * @size: the size specifier for printing.
 * Return: the number of characters printed.
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offet = 0;
	char *sttr = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (sttr == NULL)
		return (write(1, "(null)", 6));

	while (sttr[i] != '\0')
	{
		if (is_printable(sttr[i]))
			buffer[i + offet] = sttr[i];
		else
			offet += append_hexa_code(sttr[i], buffer, i + offet);

		i++;
	}

	buffer[i + offet] = '\0';

	return (write(1, buffer, i + offet));
}
/************************* PRINT REVERSE ***********************/
/**
 * print_reverse - the prints reverse string  to the buffer.
 * @types: va_list containing the string to be printed.
 * @buffer: the buffer specifier for array to handle print.
 * @flags:  Calculates active flags.
 * @width: field width to be printed.
 * @precision: the precision specificatier for printing.
 * @size: the size specifier for printing.
 * Return: the numbers of characters printed.
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - the print a string in rot13 to the buffer.
 * @types: va_list containing the string to be printed..
 * @buffer: the buffer specifier for array to handle print.
 * @flags:  the calculates specifier for active flags
 * @width: field width to be printed.
 * @precision: the precision specificatier for printing.
 * @size: the size specifier
 * Return: the numbers of characters printed.
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char xx;
	char *sttr;
	unsigned int i, j;
	int cnt = 0;
	char inn[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char ot[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	sttr = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (sttr == NULL)
		sttr = "(AHYY)";
	for (i = 0; sttr[i]; i++)
	{
		for (j = 0; inn[j]; j++)
		{
			if (inn[j] == sttr[i])
			{
				xx = ot[j];
				write(1, &xx, 1);
				cnt++;
				break;
			}
		}
		if (!inn[j])
		{
			xx = sttr[i];
			write(1, &xx, 1);
			cnt++;
		}
	}
	return (cnt);
}
