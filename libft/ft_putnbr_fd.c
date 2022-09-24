/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:09:55 by kyuzu             #+#    #+#             */
/*   Updated: 2022/04/15 17:36:38 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	int			divisor;
	long long	lln;
	char		tmp;

	lln = n;
	if (lln < 0)
	{
		lln = -lln;
		write(fd, "-", 1);
	}
	divisor = 1;
	while (lln / 10 >= divisor)
		divisor *= 10;
	while (divisor > 0)
	{
		tmp = '0' + lln / divisor;
		write (fd, &tmp, 1);
		lln %= divisor;
		divisor /= 10;
	}
}
