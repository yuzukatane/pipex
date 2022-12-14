/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:51:58 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/30 22:27:53 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_double_pointer(char **p)
{
	int	i;

	i = 0;
	while (p[i] != NULL)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

void	put_msg_and_exit(char *msg, int errno)
{
	if (msg == NULL)
		perror(NULL);
	else
		ft_putendl_fd(msg, 2);
	(void)errno;
	exit (1);
}

void	free_args(t_args *args, t_flag flag, char *msg, int errno)
{
	if (flag >= 3)
	{
		free(args->path[0]);
		free(args->path[1]);
	}
	if (flag >= 2)
	{
		free_double_pointer(args->cmd[0]);
		free_double_pointer(args->cmd[1]);
	}
	if (flag >= 1)
	{
		if (args->infile == YES)
			close(args->file[0]);
		close(args->file[1]);
	}
	free(args);
	if (flag != SUCCESS)
		put_msg_and_exit(msg, errno);
}

void	cmd_not_found(t_args *args, char *cmd, int errno, t_flag flag)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" : ", 2);
	free_args(args, flag, "command not found", errno);
}
