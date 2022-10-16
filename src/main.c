/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:27:48 by dgross            #+#    #+#             */
/*   Updated: 2022/10/16 12:57:06 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> /////////////////////////////////////////////
#include "pipex.h"
//heredoc, leak, error handling
// testen ob bei strjoin auch "/" + cmd geht

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		index;

	index = 0;
	pipex.childs = argc - 3;
	check_heredoc(&pipex, argc, argv);
	create_pipe(&pipex);
	find_path(&pipex, envp);
	while (index < pipex.childs)
	{
		childs(&pipex, index, argv[index + 2], envp);
		index++;
	}
	destroy_pipe(&pipex);
	return (0);
}
