/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:34:26 by dgross            #+#    #+#             */
/*   Updated: 2022/10/22 13:38:54 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h> // fork dup2 access
#include "libft.h" // ft_split ft_strncmp ft_strjoin
#include <stdlib.h> // exit

void	childs(t_pipex *pipex, int index, char *cmd_str, char **envp)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
		throw_error("fork error");
	if (pipex->pid == 0)
	{
		if (index == 0 && pipex->infile != -1)
			dup2_function(pipex->infile, pipex->pipe[0][1]);
		else if (index == pipex->childs - 1)
			dup2_function(pipex->pipe[index - 1][0], pipex->outfile);
		else
			dup2_function(pipex->pipe[index - 1][0], pipex->pipe[index][1]);
		destroy_pipe(pipex);
		check_access(pipex, cmd_str);
		if (execve(pipex->file, pipex->cmd, envp) == -1)
			exit(EXIT_FAILURE);
	}
}

void	check_access(t_pipex *pipex, char *cmd_str)
{
	if (access(cmd_str, F_OK) == -1)
	{
		pipex->cmd = ft_split(cmd_str, ' ');
		if (pipex->cmd == NULL)
			throw_error("ft_split error");
		pipex->file = get_path(pipex, pipex->cmd[0]);
		if (pipex->file == NULL)
			throw_error2("command not found");
	}
	else
	{
		pipex->file = cmd_str;
		pipex->cmd = ft_split(cmd_str, ' ');
	}
}

void	dup2_function(int read, int write)
{
	if (dup2(read, 0) == -1)
		throw_error("dup2 error");
	if (dup2(write, 1) == -1)
		throw_error("dup2 error");
}

void	find_path(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	pipex->path = ft_split(envp[i] + 5, ':');
	if (pipex->path == NULL)
		throw_error("ft_split error");
}

char	*get_path(t_pipex *pipex, char *cmd)
{
	int	i;

	i = 0;
	while (pipex->path[i])
	{
		pipex->path[i] = ft_strjoin(pipex->path[i], "/");
		pipex->path[i] = ft_strjoin(pipex->path[i], cmd);
		if (access(pipex->path[i], F_OK) == 0)
			return (pipex->path[i]);
		i++;
	}
	return (NULL);
}
