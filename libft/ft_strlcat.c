/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:21:10 by kyuzu             #+#    #+#             */
/*   Updated: 2022/04/19 20:45:58 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	res;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = ft_strlen(dest);
	if (i >= dstsize)
		return (dstsize + ft_strlen(src));
	res = i + ft_strlen(src);
	j = 0;
	while (src[j] != '\0' && i + 1 < dstsize)
	{
		dest[i] = src[j];
		i ++;
		j ++;
	}
	dest[i] = '\0';
	return (res);
}
