/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:09:22 by kyuzu             #+#    #+#             */
/*   Updated: 2022/04/19 20:45:34 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_byte;
	char	*src_byte;

	if (dst == src || n == 0)
		return (dst);
	else if (dst < src || dst > src + n)
		ft_memcpy(dst, src, n);
	else
	{
		dst_byte = (char *)dst;
		src_byte = (char *)src;
		i = n;
		while (i > 0)
		{
			i--;
			dst_byte[i] = src_byte[i];
		}
	}
	return (dst);
}
