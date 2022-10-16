/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:50:50 by dgross            #+#    #+#             */
/*   Updated: 2022/10/16 19:41:02 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <unistd.h> // pipe close
#include <stdlib.h> // free
#include <stdio.h> // free

void	create_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
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