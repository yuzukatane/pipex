/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:42:39 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/24 12:29:30 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	get_nbr_str(char const *s, char c)
{
	size_t	i;
	size_t	nbr_str;

	i = 0;
	nbr_str = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		nbr_str++;
	}
	if (ft_strlen(s) != 0 && s[ft_strlen(s) - 1] == c)
		nbr_str -= 1;
	return (nbr_str);
}

int	*get_nbr_char(int nbr_str, char const *s, char c)
{
	int		*nbr_char;
	int		n;
	size_t	i;
	size_t	j;

	nbr_char = malloc(nbr_str * sizeof(int));
	if (nbr_char == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < (size_t)nbr_str)
	{
		n = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			n++;
		}
		nbr_char[j] = n;
		j++;
	}
	return (nbr_char);
}

char	**ft_malloc(int nbr_str, int *nbr_char)
{
	char	**res;
	int		i;

	res = malloc((nbr_str + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < nbr_str)
	{
		res[i] = malloc((nbr_char[i] + 1) * sizeof(char));
		if (res[i] == NULL)
			return (NULL);
		i++;
	}
	res[nbr_str] = NULL;
	return (res);
}

char	**ft_cpy(char **res, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (res[i] != NULL)
	{
		j = 0;
		while (s[k] == c)
			k++;
		while (s[k] != c && s[k] != '\0')
		{
			res[i][j] = s[k];
			j++;
			k++;
		}
		res[i][j] = '\0';
		i++;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		nbr_str;
	int		*nbr_char;
	char	**res;

	nbr_str = get_nbr_str(s, c);
	nbr_char = get_nbr_char(nbr_str, s, c);
	if (nbr_char == NULL)
		return (NULL);
	res = ft_malloc(nbr_str, nbr_char);
	free(nbr_char);
	if (res == NULL)
		return (NULL);
	res = ft_cpy(res, s, c);
	return (res);
}
