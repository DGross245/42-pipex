/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:18:03 by dgross            #+#    #+#             */
/*   Updated: 2022/10/22 13:36:28 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <unistd.h> // close
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		index;

	index = 0;
	if (argc < 5)
		throw_error("Wrong input: ./pipex infile cmd1 cmd2 outfile");
	create_pipe(&pipex, argv, argc);
	check_heredoc(&pipex, argc, argv);
	find_path(&pipex, envp);
	while (index < pipex.childs)
	{
		childs(&pipex, index, argv[index + 2 + pipex.here_doc], envp);
		index++;
	}
	waitpid(0, &pipex.status, 0);
	close(pipex.outfile);
	close(pipex.infile);
	destroy_pipe(&pipex);
	ft_free(&pipex);
	return (WEXITSTATUS(pipex.status));
}
