/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:49:34 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/30 20:48:53 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_fd(char *argv[], t_args *args)
{
	if (args->file[0] == -1)
	{
		args->infile = NO;
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(argv[1], 2);
	}
}

void	check_cmd(t_args *args, int errno)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (args->cmd[i] == NULL)
		{
			i = 0;
			while (i < 2)
			{
				if (args->cmd[i] != NULL)
					free_double_pointer(args->cmd[i]);
				i++;
			}
			free_args(args, PF, NULL, errno);
		}
		i++;
	}
}

char	*join_three(char const *s1, char const *s2, char const *s3)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	res = malloc((int)(s1_len + s2_len + s3_len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, s1_len + 1);
	ft_strlcat(res, s2, s1_len + s2_len + 1);
	ft_strlcat(res, s3, s1_len + s2_len + s3_len + 1);
	return (res);
}

char	*check_path(t_args *args, char **all_path, char *cmd, int errno)
{
	char	*path;
	int		i;

	i = 0;
	while (all_path[i] != NULL)
	{
		path = join_three(all_path[i++], "/", cmd);
		if (path == NULL)
		{
			free_double_pointer(all_path);
			free_args(args, PFCP, NULL, errno);
		}
		else if (access(path, X_OK) == 0)
			return (path);
		else if (access(path, F_OK) == 0)
		{
			free_double_pointer(all_path);
			free(path);
			free_args(args, PFCP, NULL, errno);
		}
		free(path);
	}
	free_double_pointer(all_path);
	cmd_not_found(args, cmd, errno, PFCP);
	return (NULL);
}

char	**take_path(t_args *args, char **envp, int errno)
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
		free_args(args, PFC, NULL, errno);
	return (all_path);
}
