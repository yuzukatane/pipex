/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 21:11:04 by kyuzu             #+#    #+#             */
/*   Updated: 2022/04/18 14:54:57 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	number;
	int			flag;

	flag = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		flag = -1;
		str++;
	}
	number = 0;
	while (ft_isdigit(*str) && *str != '\0')
	{
		number *= 10;
		number = number + (*str - '0');
		str++;
	}
	return ((int)(number * flag));
}
