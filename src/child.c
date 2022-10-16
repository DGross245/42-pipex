/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:34:26 by dgross            #+#    #+#             */
/*   Updated: 2022/10/16 12:58:47 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h> // fork dup2
#include "libft.h" // ft_split ft_strncmp ft_strjoin

void	childs(t_pipex *pipex, int index, char *str, char **envp)
{
	int		id;

	id = fork();
	if (id == -1)
		throw_error("fork error");
	if (id == 0)
	{
		if (index == 0)
			dup2_function(pipex->infile, pipex->pipe[0][1]);
		else if (index == pipex->childs - 1)
			dup2_function(pipex->pipe[index - 1][0], pipex->outfile);
		else
			dup2_function(pipex->pipe[index - 1][0], pipex->pipe[index][1]);
		pipex->cmd = ft_split(str, ' ');
		pipex->file = get_path(pipex, pipex->cmd[0]);
		if (pipex->file == NULL)
			throw_error("cmd not found");
		execve(pipex->file, pipex->cmd, envp);
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