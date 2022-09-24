/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:51:24 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/24 16:04:38 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "libft/libft.h"
#include "pipex.h"
#include "unistd.h"
#include "stdlib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

typedef struct s_args {
	int		*file;
	char	***cmd;
	char	**path;
}	t_args;

void	check_fd(int file1, int file2);
void	check_cmd(char **cmd1, char **cmd2);
void	free_double_pointer(char **p);
void	put_msg_and_exit(char *msg);

void	pipex(int file[2], char **cmd[2], char *path[2], char **envp);

char	**take_path(char **envp, char **cmd1, char **cmd2);
char	*check_path(char **cmd, char **all_path, char **other_cmd);

#endif