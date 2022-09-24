/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:14:26 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/24 22:59:09 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_args	*init_args(int n, int errno)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (args == NULL)
		put_msg_and_exit(NULL, errno);
	args->cmd = malloc(sizeof(char **) * (n + 1));
	args->path = malloc(sizeof(char *) * (n + 1));
	if (args->cmd == NULL || args->path == NULL)
		put_msg_and_exit(NULL, errno);
	return (args);
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
		else if (access(path, F_OK) == 0)////permission denied になって欲しい
			free_args(args, 1, NULL, errno);
		free(path);
		i++;
	}
	free_args(args, 1, "Command not found", errno);
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
