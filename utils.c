/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:08:20 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/24 15:36:55 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_fd(int file1, int file2)
{
	if (file1 == -1 || file2 == -1)
	{
		perror(NULL);
		exit(1);
	}
}

void	check_cmd(char **cmd1, char **cmd2)
{
	if (cmd1 == NULL)
	{
		perror(NULL);
		exit(1);
	}
	else if (cmd2 == NULL)
	{
		free_double_pointer(cmd1);
		perror(NULL);
		exit(1);
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

void	put_msg_and_exit(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit (1);
}