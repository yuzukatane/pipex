/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:01:29 by kyuzu             #+#    #+#             */
/*   Updated: 2022/06/23 10:18:20 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(long long n, char *base)
{
	long long	divisor;
	char		tmp;
	int			len;
	int			base_len;

	len = 0;
	base_len = ft_strlen(base);
	if (n < 0)
	{
		n *= -1;
		ft_putchar('-');
		len++;
	}
	divisor = 1;
	while (n / base_len >= divisor)
		divisor *= base_len;
	while (divisor > 0)
	{
		tmp = base[n / divisor];
		write (1, &tmp, 1);
		n %= divisor;
		divisor /= base_len;
		len++;
	}
	return (len);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr_ull(unsigned long long n)
{
	unsigned long long	divisor;
	char				tmp;
	int					len;

	len = 0;
	divisor = 1;
	while (n / 10 >= divisor)
		divisor *= 10;
	while (divisor > 0)
	{
		tmp = '0' + n / divisor;
		write (1, &tmp, 1);
		n %= divisor;
		divisor /= 10;
		len++;
	}
	return (len);
}

int	ft_put_ad(unsigned long long n, char *base)
{
	int					len;
	unsigned long long	divisor;
	char				tmp;
	int					base_len;

	ft_putstr("0x");
	len = 2;
	base_len = ft_strlen(base);
	divisor = 1;
	while (n / base_len >= divisor)
		divisor *= base_len;
	while (divisor > 0)
	{
		tmp = base[n / divisor];
		write (1, &tmp, 1);
		n %= divisor;
		divisor /= base_len;
		len++;
	}
	return (len);
}

int	ft_putstr(char *s)
{
	int	len;

	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}
