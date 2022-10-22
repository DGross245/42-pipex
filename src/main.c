/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:27:48 by dgross            #+#    #+#             */
/*   Updated: 2022/10/22 13:30:25 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <fcntl.h> // open
#include <unistd.h> // close

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		index;

	index = 0;
	if (argc != 5)
		throw_error("Wrong input: ./pipex infile cmd1 cmd2 outfile");
	pipex.childs = argc - 3;
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile == -1)
		throw_error3("Wrong input: infile Error");
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
	waitpid(0, &pipex.status, 0);
	ft_close(&pipex);
	destroy_pipe(&pipex);
	ft_free(&pipex);
	return (WEXITSTATUS(pipex.status));
}

void	ft_close(t_pipex *pipex)
{
	close(pipex->outfile);
	close(pipex->infile);
}
