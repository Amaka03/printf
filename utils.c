#include "main.h"

/**
 * is_printable - Evaluates if a char is printable
 * @c: to be evaluated characters.
 * Return: 1 if c is printable, 0 if c is not printable
 */

int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - to Append ascci in hexadecimal code to buffer
 * @buffer: Array of characters.
 * @i: Index at the start of append.
 * @ascii_code: ASSCI CODE.
 * Return: 3.
 */

int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";
	/* hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if a character is digit
 * @c: evaluated character
 * Return: 1 if c is a digit, 0 if c is not a digit
 */

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - appends number to specified size
 * @num: Number to be converted.
 * @size: Number type to be converted.
 * Return: Number value
 */

long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - appends number to specified size
 * @num: Number to be converted.
 * @size: Number type to be converted.
 * Return: Number value
 */

long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
