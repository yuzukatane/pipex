/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:50:07 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/24 22:51:58 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_args	*args;
	char	**all_path;
	int		nbr;
	int		i;
	int		errno;

	if (argc < 5)
		put_msg_and_exit("too few arguments", errno);
	nbr = argc - 3;
	args = init_args(nbr, errno);
	args->file[0] = open(argv[1], O_RDONLY);
	args->file[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	check_fd(args, errno);
	i = -1;
	while (++i < nbr)
		args->cmd[i] = ft_split(argv[i + 2], ' ');
	args->cmd[i] = NULL;
	check_cmd(args, nbr, errno);
	all_path = take_path(args, envp, errno);
	i = -1;
	while (++i < nbr)
		args->path[i] = check_path(args, all_path, i, errno);
	args->path[i] = NULL;
	
	pipex(args, envp, errno);
	
	return (0);
}

void	before_pipe(t_args *args, int pfd[2], char **envp, int errno)
{
	dup2(args->file[0], STDIN_FILENO);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[0]);
	close(pfd[1]);
	if (execve(args->path[0], args->cmd[0], envp) == -1)
		free_args(args, 1, NULL, errno);
}

void	after_pipe(t_args *args, int pfd[2], char **envp, int errno)
{
	dup2(pfd[0], STDIN_FILENO);
	dup2(args->file[1], STDOUT_FILENO);
	close(pfd[0]);
	close(pfd[1]);
	if (execve(args->path[1], args->cmd[1], envp) == -1)
		free_args(args, 1, NULL, errno);
}

void	pipex(t_args *args, char **envp, int errno)
{
	int pfd[2];
	int	pid1;
	int	pid2;

	if (pipe(pfd) == -1)
		free_args(args, 1, NULL, errno);
	pid1 = fork();
	if (pid1 == -1)
		free_args(args, 1, NULL, errno);
	if (pid1 == 0)
		before_pipe(args, pfd, envp, errno);
	pid2 = fork();
	if (pid2 == -1)
		free_args(args, 1, NULL, errno);
	if (pid2 == 0)
		after_pipe(args, pfd, envp, errno);
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

/*
void	pipex(t_args *args, char **envp, int nbr)
{
	int	*pids;
	int	**pipes;
	int	i;

	pids = malloc(sizeof(int) * nbr);
	if (pids == NULL)
	{
		free_args(args, 1, NULL);
	}
	pipes = malloc(sizeof(int) * (nbr + 1));
	if (pipes == NULL)
	{
		free(pids);
		free_args(args, 1, NULL);
	}
	
	
	if (pipe(pfd) == -1)
		free_args(args, 1, NULL);
	pid1 = fork();
	if (pid1 == -1)
		free_args(args, 1, NULL);
	if (pid1 == 0)
	{
		dup2(args->file[0], STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[0]);
		close(pfd[1]);
		execve(args->path[0], args->cmd[0], envp);
	}
	pid2 = fork();
	if (pid2 == -1)
		free_args(args, 1, NULL);
	if (pid2 == 0)
	{
		dup2(pfd[0], STDIN_FILENO);
		dup2(args->file[1], STDOUT_FILENO);
		close(pfd[0]);
		close(pfd[1]);
		execve(args->path[1], args->cmd[1], envp);
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

*/
