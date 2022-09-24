/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:47:36 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/25 00:33:13 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_args	*init_args(int n)
{
	t_args	*args;
	int		errno;

	errno = 0;
	args = malloc(sizeof(t_args));
	if (args == NULL)
		put_msg_and_exit(NULL, errno);
	args->cmd = malloc(sizeof(char **) * (n + 1));
	args->path = malloc(sizeof(char *) * (n + 1));
	if (args->cmd == NULL || args->path == NULL)
		put_msg_and_exit(NULL, errno);
	return (args);
}

void	creat_cmd_and_path(t_args *args, int nbr, char *argv[], char **envp)
{
	int		i;
	int		errno;
	char	**all_path;

	i = 0;
	errno = 0;
	while (i < nbr)
	{
		args->cmd[i] = ft_split(argv[i + 2], ' ');
		i++;
	}
	args->cmd[i] = NULL;
	check_cmd(args, nbr, errno);
	all_path = take_path(args, envp, errno);
	i = 0;
	while (i < nbr)
	{
		args->path[i] = check_path(args, all_path, i, errno);
		i++;
	}
	free_double_pointer(all_path);
	args->path[i] = NULL;
}
