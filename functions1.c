#include "main.h"
/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - the prints an unsigned number to the buffer.
 * @types: va_list containing the unsigned int to be printed.
 * @buffer: buffer specifier for array to handle print
 * @flags:  the calculates specifier for active flags.
 * @width:  field width to be printed.
 * @precision: the precision specifier for printing.
 * @size: the size specifier for printing.
 * Return: the number of characters printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int nm = va_arg(types, unsigned long int);

	nm = convert_size_unsgnd(nm, size);

	if (nm == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (nm > 0)
	{
		buffer[i--] = (nm % 10) + '0';
		nm /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - prints an unsigned number in octal to the buffer.
 * @types: va_list containing the unsigned int to be printed.
 * @buffer: the buffer specifier for array to handle print.
 * @flags:  the calculates specifier for active flags.
 * @width:  field width to be printed.
 * @precision: the precision specificatier  for printing.
 * @size: the size specifier for printing.
 * Return: the number of characters printed.
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int nm = va_arg(types, unsigned long int);
	unsigned long int init_nm = nm;

	UNUSED(width);

	nm = convert_size_unsgnd(nm, size);

	if (nm == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (nm > 0)
	{
		buffer[i--] = (nm % 8) + '0';
		nm /= 8;
	}

	if (flags & F_HASH && init_nm != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - prints an unsigned number in hexadecimal to the buffer.
 * @types: va_list containing the unsigned int to be printed.
 * @buffer: the buffer specifier for array to handle print.
 * @flags:  the calculates specifier for active flags.
 * @width: field width to be printed.
 * @precision: the precision specifier for printing.
 * @size: the size specifier for printing.
 * Return: the number of characters printed.
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}
/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - prints an unsigned number in upper hexadecimal notation.
 * @types: va_list containing the unsigned int to be printed.
 * @buffer: the buffer specifier for array to handle print
 * @flags:  the calculates specifier for active flags
 * @width: field width to be printed.
 * @precision: the srecision specification for printing.
 * @size: the size specifier for printing.
 * Return: the number of characters printed.
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}
/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - the prints a hexadecimal number in lower or upper.
 * @types: Lista of arguments.
 * @map_to: Array of values to map the number to.
 * @buffer: the buffer specifier for array to handle print.
 * @flags:  the calculates specifier for active flags.
 * @flag_ch: the calculates specifier for active flags.
 * @width:  field width to be printed.
 * @precision: Precision specification.
 * @size: Size specifier.
 * @size: the size specifier for printing.
 * Return: the number of characters printed.
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int nm = va_arg(types, unsigned long int);
	unsigned long int init_nm = nm;

	UNUSED(width);

	nm = convert_size_unsgnd(nm, size);

	if (nm == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (nm > 0)
	{
		buffer[i--] = map_to[nm % 16];
		nm /= 16;
	}

	if (flags & F_HASH && init_nm != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
