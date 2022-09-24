/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:50:07 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/24 21:41:18 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_args	*init_args(int n)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (args == NULL)
		put_msg_and_exit("failed to allocate memory");
	args->cmd = malloc(sizeof(char **) * (n + 1));
	args->path = malloc(sizeof(char *) * (n + 1));
	if (args->cmd == NULL || args->path == NULL)
		put_msg_and_exit("failed to allocate memory");
	return (args);
}

int	main(int argc, char *argv[], char **envp)
{
	t_args	*args;
	char	**all_path;
	int		nbr;
	int		i;

	if (argc < 5)
		put_msg_and_exit("too few arguments");
	nbr = argc - 3;
	args = init_args(nbr);
	args->file[0] = open(argv[1], O_RDONLY);
	args->file[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	check_fd(args);
	i = -1;
	while (++i < nbr)
		args->cmd[i] = ft_split(argv[i + 2], ' ');
	args->cmd[i] = NULL;
	check_cmd(args, nbr);
	all_path = take_path(args, envp);
	i = -1;
	while (++i < nbr)
		args->path[i] = check_path(args, all_path, i);
	args->path[i] = NULL;
	
	pipex(args, envp);
	
	// int pfd[2];
	// if (pipe(pfd) == -1)
	// {
	// 	perror("pfd error\n");
	// 	return (1);
	// }
	// int pid1 = fork();
	// if (pid1 == -1)
	// {
	// 	perror("pid1 error\n");
	// 	return (2);
	// }
	// if (pid1 == 0)
	// {
	// 	dup2(file[0], STDIN_FILENO);
	// 	dup2(pfd[1], STDOUT_FILENO);
	// 	close(pfd[0]);
	// 	close(pfd[1]);
	// 	execve(path[0], cmd1, envp);
	// }
	// int pid2 = fork();
	// if (pid2 == -1)
	// {
	// 	perror("pid2 error\n");
	// 	return(3);
	// }
	// if (pid2 == 0)
	// {
	// 	dup2(pfd[0], STDIN_FILENO);
	// 	dup2(file[1], STDOUT_FILENO);
	// 	close(pfd[0]);
	// 	close(pfd[1]);
	// 	execve(path[1], cmd2, envp);
	// }
	// close(pfd[0]);
	// close(pfd[1]);
	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);

	return (0);
}

// void	before_pipe(t_args *args, int pfd[2], char **envp)
// {
// 	dup2(args->file[0], STDIN_FILENO);
// 	dup2(pfd[1], STDOUT_FILENO);
// 	close(pfd[0]);
// 	close(pfd[1]);
// 	execve(args->path[0], args->cmd[0], envp);
// }

// void	after_pipe(t_args *args, int pfd[2], char **envp)
// {
// 	dup2(pfd[0], STDIN_FILENO);
// 	dup2(args->file[1], STDOUT_FILENO);
// 	close(pfd[0]);
// 	close(pfd[1]);
// 	execve(args->path[1], args->cmd[1], envp);
// }

void	pipex(t_args *args, char **envp)
{
	int pfd[2];
	int	pid1;
	int	pid2;

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

char	*check_path(t_args *args, char **all_path, int nbr)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (all_path[i] != NULL)
	{
		tmp = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(tmp, *args->cmd[nbr]);
		free(tmp);
		if (path == NULL)
		{
			free_double_pointer(all_path);
			free_args(args, 1, "failed to allocate memory");
		}
		else if (access(path, X_OK) == 0)
			return (path);
		else if (access(path, F_OK) == 0)////permission denied になって欲しい
			free_args(args, 1, NULL);
		free(path);
		i++;
	}
	free_args(args, 1, "command not found");
	return (NULL);
}

char	**take_path(t_args *args, char **envp)
{
	char	**all_path;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		else
			i++;
	}
	all_path = ft_split(envp[i], ':');
	if (all_path == NULL)
		free_args(args, 1, "failed to allocate memory");
	return (all_path);
}
