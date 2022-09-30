/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:47:36 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/30 19:03:03 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_args	*init_args(void)
{
	t_args	*args;
	int		errno;

	errno = 0;
	args = malloc(sizeof(t_args));
	if (args == NULL)
		put_msg_and_exit(NULL, errno);
	args->infile = YES;
	return (args);
}

void	is_null(t_args *args, int errno)
{
	if (args->cmd[0][0] == NULL || args->cmd[1][0] == NULL)
		cmd_not_found(args, " ", errno, PFC);
}

void	creat_cmd_and_path(t_args *args, char *argv[], char **envp)
{
	int		errno;
	char	**all_path;

	errno = 0;
	args->cmd[0] = ft_split(argv[2], ' ');
	args->cmd[1] = ft_split(argv[3], ' ');
	check_cmd(args, errno);
	is_null(args, errno);
	all_path = take_path(args, envp, errno);
	args->path[0] = NULL;
	args->path[1] = NULL;
	args->path[0] = check_path(args, all_path, args->cmd[0][0], errno);
	args->path[1] = check_path(args, all_path, args->cmd[1][0], errno);
	free_double_pointer(all_path);
}
