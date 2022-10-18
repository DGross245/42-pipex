/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:52:08 by dgross            #+#    #+#             */
/*   Updated: 2022/10/18 14:15:20 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"
#include <unistd.h> // pipe close
#include <stdlib.h> // free
#include <stdio.h> // free

void	create_pipe(t_pipex *pipex, char **argv, int argc)
{
	int	i;

	i = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		pipex->here_doc = 1;
	else
		pipex->here_doc = 0;
	pipex->childs = argc - 3 - pipex->here_doc;
	alloc_pipe(pipex);
	while (i < pipex->childs - 1)
	{
		if (pipe(pipex->pipe[i]) == -1)
			throw_error("Open pipe Error");
		i++;
	}
}

void	destroy_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->childs - 1)
	{
		close(pipex->pipe[i][0]);
		close(pipex->pipe[i][1]);
		free(pipex->pipe[i]);
		i++;
	}
	free(pipex->pipe);
}

void	alloc_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->pipe = ft_malloc(sizeof(int *) * (pipex->childs - 1));
	if (pipex->pipe == NULL)
		throw_error("Malloc error");
	while (i < pipex->childs - 1)
	{
		pipex->pipe[i] = ft_malloc(sizeof(int) * 2);
		if (pipex->pipe[i] == NULL)
			throw_error("Malloc Error");
		i++;
	}
}

void	ft_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->path[i] != NULL)
	{
		free(pipex->path[i]);
		i++;
	}
	free(pipex->path);
}
