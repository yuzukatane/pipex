/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:51:24 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/24 22:50:24 by kyuzu            ###   ########.fr       */
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
	int		file[2];
	char	***cmd;
	char	**path;
}	t_args;

void	check_fd(t_args *args, int errno);
void	check_cmd(t_args *args, int nbr, int errno);
void	free_double_pointer(char **p);
void	free_args(t_args *args, int flag, char *msg, int errno);
void	put_msg_and_exit(char *msg, int errno);

void	pipex(t_args *args, char **envp, int errno);

t_args	*init_args(int n, int errno);
char	**take_path(t_args *args, char **envp, int errno);
char	*check_path(t_args *args, char **all_path, int nbr, int errno);



#endif