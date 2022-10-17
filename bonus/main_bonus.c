/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:18:03 by dgross            #+#    #+#             */
/*   Updated: 2022/10/17 23:46:30 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h> // open
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		index;

	if (argc < 5)
		throw_error("Wrong input: ./pipex infile cmd1 cmd2 outfile");
	index = 0;
	check_heredoc(&pipex, argc, argv);
	pipex.childs = argc - 3 - pipex.here_doc;
	create_pipe(&pipex);
	find_path(&pipex, envp);
	while (index < pipex.childs)
	{
		childs(&pipex, index, argv[index + 2], envp);
		index++;
	}
	close(pipex.outfile);
	close(pipex.infile);
	destroy_pipe(&pipex);
	ft_free(&pipex);
	return (0);
}
