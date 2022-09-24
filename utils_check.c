/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:49:34 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/25 00:29:37 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_fd(t_args *args, int errno)
{
	if (args->file[0] == -1 || args->file[1] == -1)
	{
		free_args(args, 0, NULL, errno);
	}
}

void	check_cmd(t_args *args, int nbr, int errno)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		if (args->cmd[i] == NULL)
		{
			i = 0;
			while (i < nbr)
			{
				if (args->cmd[i] != NULL)
					free_double_pointer(args->cmd[i]);
				i++;
			}
			free_args(args, 0, NULL, errno);
		}
		i++;
	}
}

char	*check_path(t_args *args, char **all_path, int nbr, int errno)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (all_path[i] != NULL)
	{
		tmp = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(tmp, *args->cmd[nbr]);
		free(tmp);
		if (path == NULL)
		{
			free_double_pointer(all_path);
			free_args(args, 1, NULL, errno);
		}
		else if (access(path, X_OK) == 0)
			return (path);
		else if (access(path, F_OK) == 0)
		{
			free(path);
			free_args(args, 1, NULL, errno);
		}
		free(path);
		i++;
	}
	cmd_not_found(args, nbr, errno);
	return (NULL);
}

char	**take_path(t_args *args, char **envp, int errno)
{
	char	**all_path;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		else
			i++;
	}
	all_path = ft_split(envp[i], ':');
	if (all_path == NULL)
		free_args(args, 1, NULL, errno);
	return (all_path);
}
