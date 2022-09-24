/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:51:58 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/25 00:07:52 by kyuzu            ###   ########.fr       */
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
	int	er_nb;

	er_nb = errno;
	if (msg == NULL)
		perror(NULL);
	else
		ft_putendl_fd(msg, 2);
	exit (1);
}

void	free_args(t_args *args, int flag, char *msg, int errno)
{
	int	i;

	if (flag > 0)
	{
		i = -1;
		while (args->cmd[++i] != NULL)
			free_double_pointer(args->cmd[i]);
	}
	free(args->cmd);
	free(args->path);
	free(args);
	put_msg_and_exit(msg, errno);
}

void	cmd_not_found(t_args *args, int nbr, int errno)
{
	ft_putstr_fd(*args->cmd[nbr], 2);
	ft_putstr_fd(" : ", 2);
	free_args(args, 1, "command not found", errno);
}
