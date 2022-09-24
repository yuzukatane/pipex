/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:36:32 by kyuzu             #+#    #+#             */
/*   Updated: 2022/04/19 20:45:12 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_get_size(long long n)
{
	int	size;

	if (n < 0)
		n = -n;
	size = 0;
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_to_array(long long n, char *res)
{
	int		divisor;
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		res[i] = '-';
		i++;
	}
	divisor = 1;
	while (n / 10 >= divisor)
		divisor *= 10;
	while (divisor > 0)
	{
		res[i] = '0' + n / divisor;
		n %= divisor;
		divisor /= 10;
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			size;
	long long	lln;

	lln = n;
	size = ft_get_size(lln);
	if (n > 0)
		res = malloc((size + 1) * sizeof(char));
	else
		res = malloc((size + 2) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res = ft_to_array(lln, res);
	return (res);
}
