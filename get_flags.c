#include "main.h"
/**
  * get_flags - for calculates active flags
  * @format: the formatted string to prints the arguments
  * @i: index in the format string.
  * Return: the integer representing the flags.
  */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int n, cur_i;
	int flg = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (cur_i = *i + 1; format[cur_i] != '\0'; cur_i++)
	{
		for (n = 0; FLAGS_CH[n] != '\0'; n++)
			if (format[cur_i] == FLAGS_CH[n])
			{
				flg |= FLAGS_ARR[n];
				break;
			}

		if (FLAGS_CH[n] == 0)
			break;
	}

	*i = cur_i - 1;

	return (flg);
}
