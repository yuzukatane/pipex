/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:37:50 by kyuzu             #+#    #+#             */
/*   Updated: 2022/04/14 18:13:33 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	ft_get_start(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
				break ;
			else if (set[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

size_t	ft_get_end(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(s1) == 0)
		return (0);
	i = ft_strlen(s1) - 1;
	while (i != 0)
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
				break ;
			else if (set[j + 1] == '\0')
				return (i);
			j++;
		}
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	start;
	size_t	end;

	if (ft_strlen(set) == 0)
	{
		start = 0;
		end = ft_strlen(s1) - 1;
	}
	else
	{
		start = ft_get_start(s1, set);
		end = ft_get_end(s1, set);
	}
	res = ft_substr(s1, start, end - start + 1);
	return (res);
}
