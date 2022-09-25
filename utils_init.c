/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:47:36 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/25 11:08:20 by kyuzu            ###   ########.fr       */
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
	return (args);
}

void	creat_cmd_and_path(t_args *args, char *argv[], char **envp)
{
	int		errno;
	char	**all_path;

	errno = 0;
	args->cmd[0] = ft_split(argv[2], ' ');
	args->cmd[1] = ft_split(argv[3], ' ');
	check_cmd(args, errno);
	all_path = take_path(args, envp, errno);
	args->path[0] = NULL;
	args->path[1] = NULL;
	args->path[0] = check_path(args, all_path, args->cmd[0][0], errno);
	args->path[1] = check_path(args, all_path, args->cmd[1][0], errno);
	free_double_pointer(all_path);
}
