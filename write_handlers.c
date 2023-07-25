#include "main.h"

/********* WRITE HANDLE *********/
/**
 * handle_write_char - Prints string to buffer
 * @c: type of character.
 * @buffer: Buffer to handle print
 * @flags:  Calculates all the active flags.
 * @width: get the width.
 * @precision: print precision specifier
 * @size: print Size specifier.
 * Return: Number of characters printed.
 */

int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int x = 0;
	char pa = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		pa = '0';

	buffer[x++] = c;
	buffer[x] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (x = 0; x < width - 1; x++)
			buffer[BUFF_SIZE - x - 2] = pa;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - x - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - x - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/********* WRITE NUMBER *********/
/**
 * write_number - Prints string to buffer
 * @is_negative: List of all arguments
 * @ind: types of character.
 * @buffer: Buffer to handle print
 * @flags:  Calculates all the active flags.
 * @width: get the width.
 * @precision: print precision specifier
 * @size: print Size specifier.
 * Return: Number of characters printed.
 */

int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int lnth = BUFF_SIZE - ind - 1;
	char pa = ' ', ext_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pa = '0';
	if (is_negative)
		ext_ch = '-';
	else if (flags & F_PLUS)
		ext_ch = '+';
	else if (flags & F_SPACE)
		ext_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		lnth, pa, ext_ch));
}

/********* WRITE NUM *********/
/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer to handle print
 * @flags:  Calculates all the active flags.
 * @width: get the width.
 * @precision: print precision specifier
 * @size: print Size specifier.
 * @length: length of Number
 * @padd: Padding characters
 * @extra_c: Extra characters.
 * Return: Number of characters printed.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int x, pd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (x = 1; x < width - length + 1; x++)
			buffer[x] = padd;
		buffer[x] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], x - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], x - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--pd_start] = extra_c;
			return (write(1, &buffer[pd_start], x - pd_start) +
				write(1, &buffer[ind], length - (1 - pd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/*************WRITE_UNSIGNED***************/
/**
 * write_unsgnd - Writes unsigned number specified
 * @is_negative: List of all arguments
 * @ind: types of character.
 * @buffer: Buffer to handle print
 * @flags:  Calculates all the active flags.
 * @width: get the width.
 * @precision: print precision specifier
 * @size: print Size specifier.
 * Return: Number of characters printed.
 */

int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int lnth = BUFF_SIZE - ind - 1, i = 0;
	char pd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < lnth)
		pd = ' ';

	while (precision > lnth)
	{
		buffer[--ind] = '0';
		lnth++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pd = '0';

	if (width > lnth)
	{
		for (i = 0; i < width - lnth; i++)
			buffer[i] = pd;

		buffer[i] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>pd]*/
		{
			return (write(1, &buffer[ind], lnth) + write(1, &buffer[0], i));
		}
		else /* Asign extra char to left of padding [pd>buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], lnth));
		}
	}

	return (write(1, &buffer[ind], lnth));
}

/***********WRITE_POINTER**************/
/**
 * write_pointer - Write memory address
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer to handle print
 * @flags:  Calculates all the active flags.
 * @width: get the width.
 * @precision: print precision specifier
 * @size: print Size specifier
 * @length: length of Number
 * @padd: Padding characters
 * @extra_c: Extra characters.
 * @padd_start: Index of padding start
 * Return: Number of characters printed.
 */

int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int x;

	if (width > length)
	{
		for (x = 3; x < width - length + 3; x++)
			buffer[x] = padd;
		buffer[x] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], x - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], x - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], x - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
