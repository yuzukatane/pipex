/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:14:40 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/24 22:46:35 by kyuzu            ###   ########.fr       */
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
