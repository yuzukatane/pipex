/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 10:18:29 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/19 13:55:42 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_distribution(const char **format, va_list args, int len, char *str)
{
	(*format)++;
	if (**format == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (**format == 's')
	{
		str = va_arg(args, char *);
		if (str == NULL)
			len += ft_putstr("(null)");
		else
			len += ft_putstr(str);
	}
	else if (**format == 'p')
		len += ft_put_ad(va_arg(args, unsigned long long), "0123456789abcdef");
	else if (**format == 'd' || **format == 'i')
		len += ft_putnbr_base(va_arg(args, int), "0123456789");
	else if (**format == 'u')
		len += ft_putnbr_ull(va_arg(args, unsigned int));
	else if (**format == 'x')
		len += ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef");
	else if (**format == 'X')
		len += ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (**format == '%')
		len += ft_putchar('%');
	(*format)++;
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	unsigned int	len;
	char			*str;

	len = 0;
	str = NULL;
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
			len = ft_distribution(&format, args, len, str);
		while (*format != '%' && *format != '\0')
		{
			ft_putchar(*format);
			format++;
			len++;
		}
		if (len >= INT_MAX)
			return (-1);
	}
	va_end(args);
	return ((int)len);
}
