/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:53:09 by dgross            #+#    #+#             */
/*   Updated: 2022/10/18 17:09:22 by dgross           ###   ########.fr       */
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
	if (pipex->here_doc == 1)
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
		pipex->limiter = argv[2];
		ft_here_doc(pipex);
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
	int		limit_len;
	int		i;

	i = 0;
	length = 65535;
	input = ft_malloc (length * sizeof(char));
	pipex->limiter = ft_strjoin(pipex->limiter, "\n");
	limit_len = ft_strlen(pipex->limiter);
	while (1)
	{
		pipex->infile = pipex->pipe[0][0];
		write_pipes(pipex);
		i = read(STDOUT_FILENO, input, length);
		if (i == -1)
			throw_error("read error");
		input[i] = 0;
		if (ft_strncmp(input, pipex->limiter, limit_len) == 0)
			break ;
		write(pipex->pipe[0][1], input, ft_strlen(input));
	}
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
