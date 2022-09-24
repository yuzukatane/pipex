/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 20:35:12 by kyuzu             #+#    #+#             */
/*   Updated: 2022/04/12 10:00:57 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sbyte;
	unsigned char	cbyte;
	size_t			i;

	if (n == 0)
		return (NULL);
	sbyte = (unsigned char *)s;
	cbyte = (unsigned char)c;
	i = 0;
	while (sbyte[i] != cbyte)
	{
		if (i + 1 == n)
			return (NULL);
		i++;
	}
	return (&sbyte[i]);
}
