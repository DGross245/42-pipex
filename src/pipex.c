/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:27:48 by dgross            #+#    #+#             */
/*   Updated: 2022/10/13 18:36:35 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> /////////////////////////////////////////////
#include "pipex.h"
#include <fcntl.h> // open
#include <stdlib.h> // exit
#include <unistd.h> // fork dup2

//heredoc, cmd path etc, child manegmentos, leak, error handling
void	throw_error(char *str);
void	create_pipe(t_pipex pipex);
void	alloc_pipe(t_pipex pipex);
void	childs(t_pipex pipex);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;

	i = 0;
	if (argc != 5)
		throw_error("Wrong input: ./pipex infile cmd1 cmd2 outfile");
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[argc - 1], O_WRONLY);
	if (pipex.infile == -1 || pipex.outfile == -1)
		throw_error("Wrong input: infile/outfile Error");
	pipex.childs = argc - 3;
	create_pipe(pipex);
	find_cmd(pipex, envp);
	while (i < pipex.childs)
	{
		childs(pipex, envp);
		i++;
	}
	destroy_pipe(pipex);
	return (0);
}

void	find_cmd(pipex, envp)
{
	
}

void	childs(t_pipex pipex, char **envp)
{
	int	id;

	id = fork();
	if (id == -1)
		throw_error("fork error");
	if (id == 0)
	{
		close(pipex.pipe[i][0]);
		dup2(pipex.infile, 0);
		dup2(pipex.pipe[i][1], 1);
		execve(path, cmd);
	}
}

void	create_pipe(t_pipex pipex)
{
	int i;

	i = 0;
	alloc_pipe(pipex);
	while (1 < pipex.childs - 1)
	{
		if (pipe(pipex.pipe[i]) == -1)
			throw_error("Open pipe Error");
		i++;
	}
}

void	destroy_pipe(t_pipex pipex)
{
	int	i;

	i = 0;
	while (1 < pipex.childs - 1)
	{
		close(pipex.pipe[i]);
		i++;
	}
}

void	alloc_pipe(t_pipex pipex)
{
	int	i;

	i = 0;
	pipex.pipe = (int **)malloc(sizeof(int *) * pipex.child - 1);
	if (pipex.pipe == NULL)
		throw_error("Malloc error");
	while (pipex.pipe[i] != NULL)
	{
		pipex.pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (pipex.pipe[i] == NULL)
			throw_error("Malloc Error");
		i++;
	}
}

void	throw_error(char *str)
{
	perror(str);
	exit(0);
}
