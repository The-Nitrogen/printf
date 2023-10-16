#include "main.h"

void printf_buffer(char buffer[], int *printf_ind);

/**
 * my_printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int my_printf(const char *format, ...)
{
	int i, printed = 0, printed_count = 0;
	int flags, width, precision, size, printf_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[printf_ind++] = format[i];
			if (printf_ind == BUFF_SIZE)
				printf_buffer(buffer, &printf_ind);
			/* write(1, &format[i], 1);*/
			printed_count++;
		}
		else
		{
			printf_buffer(buffer, &printf_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_count += printed;
		}
	}

	printf_buffer(buffer, &printf_ind);

	va_end(list);

	return (printed_count);
}
