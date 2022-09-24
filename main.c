/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuzu <kyuzu@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:50:07 by kyuzu             #+#    #+#             */
/*   Updated: 2022/09/25 00:21:19 by kyuzu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_args	*args;
	int		nbr;
	int		errno;

	errno = 0;
	if (argc < 5)
		put_msg_and_exit("too few arguments", errno);
	nbr = argc - 3;
	args = init_args(nbr);
	args->file[0] = open(argv[1], O_RDONLY);
	args->file[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT);
	check_fd(args, errno);
	creat_cmd_and_path(args, nbr, argv, envp);
	pipex(args, envp, errno);
	free_args(args, 2, NULL, errno);
	return (0);
}
