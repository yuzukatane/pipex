/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:50:07 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/30 19:18:58 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_args	*args;
	int		errno;

	errno = 0;
	if (argc < 5)
		put_msg_and_exit("too few arguments", errno);
	else if (argc > 5)
		put_msg_and_exit("too much arguments", errno);
	args = init_args();
	args->file[0] = open(argv[1], O_RDONLY);
	args->file[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	check_fd(argv, args);
	creat_cmd_and_path(args, argv, envp);
	pipex(args, envp, errno);
	free_args(args, SUCCESS, NULL, errno);
	return (0);
}
