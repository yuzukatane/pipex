/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:50:07 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/24 15:57:12 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int main(int argc, char *argv[], char **envp)
{
	int		file[2];
	char	**cmd[2];
	char	**all_path;
	char	*path[2];

	file[0] = open(argv[1], O_RDONLY);
	file[1] = open(argv[4], O_WRONLY | O_TRUNC);
	check_fd(file[0], file[1]);
	cmd[0] = ft_split(argv[2], ' ');
	cmd[1] = ft_split(argv[3], ' ');
	check_cmd(cmd[0], cmd[1]);
	all_path = take_path(envp, cmd[0], cmd[1]);
	path[0] = check_path(cmd[0], all_path, cmd[1]);
	path[1] = check_path(cmd[1], all_path, cmd[0]);
	if (path[0] == NULL || path[1] == NULL)
		put_msg_and_exit("command not found");
	
	pipex(file, cmd, path, envp);
	
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

void	pipex(int file[2], char **cmd[2], char *path[2], char **envp)
{
	int pfd[2];
	if (pipe(pfd) == -1)
	{
		perror("pfd error\n");
		// return (1);
	}

	int pid1 = fork();
	if (pid1 == -1)
	{
		perror("pid1 error\n");
		// return (2);
	}

	if (pid1 == 0)
	{
		dup2(file[0], STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[0]);
		close(pfd[1]);
		execve(path[0], cmd[0], envp);
	}

	int pid2 = fork();
	if (pid2 == -1)
	{
		perror("pid2 error\n");
		// return(3);
	}
	if (pid2 == 0)
	{
		dup2(pfd[0], STDIN_FILENO);
		dup2(file[1], STDOUT_FILENO);
		close(pfd[0]);
		close(pfd[1]);
		execve(path[1], cmd[1], envp);
	}

	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	
}

char	*check_path(char **cmd, char **all_path, char **other_cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (all_path[i] != NULL)
	{
		tmp = ft_strjoin(all_path[i], "/");
		path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (path == NULL)
		{
			free_double_pointer(all_path);
			free_double_pointer(cmd);
			free_double_pointer(other_cmd);
			perror(NULL);
			exit(1);
		}
		else if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	**take_path(char **envp, char **cmd1, char **cmd2)
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
	{
		free_double_pointer(cmd1);
		free_double_pointer(cmd2);
		perror(NULL);
		exit(1);
	}
	return (all_path);
}
