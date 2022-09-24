/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:26:39 by kyuzu             #+#    #+#             */
/*   Updated: 2022/04/13 15:25:54 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;

	if (start >= ft_strlen(s))
	{
		res = malloc(sizeof(char));
		if (res == NULL)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	else if (s == NULL)
		return (NULL);
	if (ft_strlen(s) <= len)
		res = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	else
		res = malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, &s[start], len + 1);
	return (res);
}
