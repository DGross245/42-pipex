/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:53:09 by dgross            #+#    #+#             */
/*   Updated: 2022/10/17 17:07:45 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h> // open
#include <stdio.h> // open
#include "libft.h" // ft_strncmp

void	check_heredoc(t_pipex *pipex, int argc, char **argv)
{
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (argc < 7)
		{
			throw_error("Wrong input: ./pipex here_doc limiter \
			infile cmd1 cmd2 ... outfile");
		}
		//ft_here_doc(pipex, argv[2], argc);
	}
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile == -1)
			throw_error2("Wrong input: infile Error");
		pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (pipex->outfile == -1)
			throw_error("Wrong input: outfile Error");
	}
}

//void	ft_here_doc(t_pipex *pipex, char *limiter)
//{
	
//}
