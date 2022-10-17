/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:53:09 by dgross            #+#    #+#             */
/*   Updated: 2022/10/17 23:38:58 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h> // open
#include <stdio.h> // open
#include "libft.h" // ft_strncmp
#include "get_next_line.h" // ft_get_next_line
#include <unistd.h> // read
#include <stdlib.h> // free

void	check_heredoc(t_pipex *pipex, int argc, char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
		{
			throw_error("Wrong input: ./pipex here_doc limiter \
			cmd1 cmd2 ... outfile");
		}
		pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR \
		| O_APPEND, 0777);
		if (pipex->outfile == -1)
			throw_error("Wrong input: outfile Error");
		pipex->here_doc = 1;
		pipex->limiter = argv[2];
	}
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile == -1)
			throw_error2("Wrong input: infile Error");
		pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (pipex->outfile == -1)
			throw_error("Wrong input: outfile Error");
		pipex->here_doc = 0;
	}
}

void	ft_here_doc(t_pipex *pipex)
{
	char	*input;
	int		length;

	length = ft_strlen(pipex->limiter);
	while (1)
	{
		write_pipes(pipex);
		input = get_next_line(STDIN_FILENO);
		if (input == NULL)
			throw_error("read error");
		if (ft_strncmp(input, pipex->limiter, length) == 0)
			break ;
		write(pipex->pipe[0][1], input, ft_strlen(input));
		free(input);
	}
	close(pipex->pipe[0][1]);
	free(input);
}

void	write_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->childs - 1)
	{
		write(1, "pipe ", 5);
		i++;
	}
	write(1, "heredoc>", 8);
}
