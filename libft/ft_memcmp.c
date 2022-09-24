/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 20:35:08 by kyuzu             #+#    #+#             */
/*   Updated: 2022/04/11 11:14:52 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1byte;
	unsigned char	*s2byte;
	size_t			i;
	int				diff;

	s1byte = (unsigned char *)s1;
	s2byte = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		diff = s1byte[i] - s2byte[i];
		if (diff != 0)
			return (diff);
		i++;
	}
	return (0);
}
