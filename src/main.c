/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:27:48 by dgross            #+#    #+#             */
/*   Updated: 2022/10/18 16:57:07 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> /////////////////////////////////////////////
#include "pipex.h"
#include <fcntl.h> // open
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
//heredoc, leak, error handling
// testen ob bei strjoin auch "/" + cmd geht

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		index;

	if (argc != 5)
		throw_error("Wrong input: ./pipex infile cmd1 cmd2 outfile");
	index = 0;
	pipex.childs = argc - 3;
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile == -1)
		throw_error2("Wrong input: infile Error");
	pipex.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (pipex.outfile == -1)
		throw_error("Wrong input: outfile Error");
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
