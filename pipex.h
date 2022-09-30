/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:51:24 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/30 19:18:51 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "pipex.h"
# include "unistd.h"
# include "stdlib.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

typedef enum e_flag
{
	P,
	PF,
	PFC,
	PFCP,
	SUCCESS
}	t_flag;

enum e_infile
{
	YES,
	NO
};

typedef struct s_args
{
	int		file[2];
	char	**cmd[2];
	char	*path[2];
	int		infile;
}	t_args;

t_args	*init_args(void);
void	creat_cmd_and_path(t_args *args, char *argv[], char **envp);

void	pipex(t_args *args, char **envp, int errno);

void	check_fd(char *argv[], t_args *args);
void	check_cmd(t_args *args, int errno);
char	**take_path(t_args *args, char **envp, int errno);
char	*check_path(t_args *args, char **all_path, char *cmd, int errno);

void	free_double_pointer(char **p);
void	free_args(t_args *args, t_flag flag, char *msg, int errno);
void	put_msg_and_exit(char *msg, int errno);
void	cmd_not_found(t_args *args, char *cmd, int errno, t_flag flag);

#endif
