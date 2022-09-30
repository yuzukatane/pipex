/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:53:04 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/30 20:44:43 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	before_pipe(t_args *args, int pfd[2], char **envp, int errno)
{
	dup2(args->file[0], STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[0]);
	close(pfd[1]);
	if (execve(args->path[0], args->cmd[0], envp) == -1)
		free_args(args, PFCP, NULL, errno);
}

void	after_pipe(t_args *args, int pfd[2], char **envp, int errno)
{
	dup2(pfd[0], STDIN_FILENO);
	dup2(args->file[1], STDOUT_FILENO);
	close(pfd[0]);
	close(pfd[1]);
	if (execve(args->path[1], args->cmd[1], envp) == -1)
		free_args(args, PFCP, NULL, errno);
}

void	no_infile(t_args *args, char **envp, int errno)
{
	int	tmp_fd;

	tmp_fd = open("tmp.txt", O_RDONLY | O_CREAT, 0664);
	if (tmp_fd == -1)
		free_args(args, PFCP, NULL, errno);
	if (unlink("tmp.txt") < 0)
	{
		close(tmp_fd);
		free_args(args, PFCP, NULL, errno);
	}
	dup2(tmp_fd, STDIN_FILENO);
	dup2(args->file[1], STDOUT_FILENO);
	if (execve(args->path[1], args->cmd[1], envp) == -1)
	{
		close(tmp_fd);
		free_args(args, PFCP, NULL, errno);
	}
	close(tmp_fd);
}

void	pipex(t_args *args, char **envp, int errno)
{
	int	pfd[2];
	int	pid1;
	int	pid2;

	if (args->infile == NO)
	{
		no_infile(args, envp, errno);
		return ;
	}
	if (pipe(pfd) == -1)
		free_args(args, PFCP, NULL, errno);
	pid1 = fork();
	if (pid1 == -1)
		free_args(args, PFCP, NULL, errno);
	if (pid1 == 0)
		before_pipe(args, pfd, envp, errno);
	pid2 = fork();
	if (pid2 == -1)
		free_args(args, PFCP, NULL, errno);
	if (pid2 == 0)
		after_pipe(args, pfd, envp, errno);
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
