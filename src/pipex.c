/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:27:48 by dgross            #+#    #+#             */
/*   Updated: 2022/10/14 22:08:55 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> /////////////////////////////////////////////
#include "pipex.h"
#include "libft.h"
#include <fcntl.h> // open
#include <stdlib.h> // exit
#include <unistd.h> // fork dup2

//heredoc, cmd path etc, child manegmentos, leak, error handling
void	throw_error(char *str);
void	create_pipe(t_pipex *pipex);
void	alloc_pipe(t_pipex *pipex);
void	childs(t_pipex *pipex, int index, char *cmd, char **envp);
void	find_path(t_pipex *pipex, char **envp);
void	destroy_pipe(t_pipex *pipex);
char	*get_cmd(t_pipex *pipex, char *cmd, char *envp);

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;
	int		k;

	i = 2;
	k = 1;
	if (argc != 5)
		throw_error("Wrong input: ./pipex infile cmd1 cmd2 outfile");
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[argc - 1], O_WRONLY);
	if (pipex.infile == -1 || pipex.outfile == -1)
		throw_error("Wrong input: infile/outfile Error");
	pipex.childs = argc - 3;
	create_pipe(&pipex);
	find_path(&pipex, envp);
	while (i < pipex.childs + 2)
	{
		childs(&pipex, k, argv[i], envp);
		i++;
		k++;
	}
	destroy_pipe(&pipex);
	return (0);
}

void	find_path(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	pipex->envp = envp[i];
}

void	childs(t_pipex *pipex, int index, char *str, char **envp)
{
	int		id;
	int		i;
	char	*path;
	char	*file;
	char	**cmd;

	i = 0;
	path = ft_strdup(pipex->envp);
	id = fork();
	if (id == -1)
		throw_error("fork error");
	if (id == 0)
	{
		if (index == 1)
		{
			printf("%d\n", dup2(pipex->infile, 0));
			printf("%d\n", dup2(pipex->pipe[0][1], 1));
		}
		else if (index == pipex->childs)
		{
			dup2(pipex->pipe[i][0], 0);
			dup2(pipex->outfile, 1);
		}
		else
		{
			dup2(pipex->pipe[i][0], 0);
			dup2(pipex->pipe[i][1], 1);
		}
		cmd = ft_split(str, ' ');
		file = get_cmd(pipex, cmd[0], path);
		if (file == NULL)
			throw_error("cmd not found");
		execve(file, cmd, envp);
	}
}

char	*get_cmd(t_pipex *pipex, char *cmd, char *envp)
{
	int	i;

	i = 0;
	pipex->path = ft_split(envp + 5, ':');
	while (pipex->path[i])
	{
		pipex->path[i] = ft_strjoin(pipex->path[i], "/");
		pipex->path[i] = ft_strjoin(pipex->path[i], cmd);
		if (access(pipex->path[i], F_OK) == 0)
		{
			printf("kekw\n");
			return (pipex->path[i]);
		}
		i++;
	}
	return (NULL);
}

void	create_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	alloc_pipe(pipex);
	while (1 < pipex->childs - 1)
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
	while (1 < pipex->childs - 1)
	{
		close(pipex->pipe[i][0]);
		close(pipex->pipe[i][1]);
		i++;
	}
}

void	alloc_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->pipe = (int **)malloc(sizeof(int *) * pipex->childs - 1);
	if (pipex->pipe == NULL)
		throw_error("Malloc error");
	while (pipex->pipe[i] != NULL)
	{
		pipex->pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (pipex->pipe[i] == NULL)
			throw_error("Malloc Error");
		i++;
	}
}

void	throw_error(char *str)
{
	perror(str);
	exit(0);
}
