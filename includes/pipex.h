/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:26:19 by dgross            #+#    #+#             */
/*   Updated: 2022/10/22 13:35:29 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipex
{
	int		**pipe;
	int		pid;
	char	**path;
	char	*file;
	char	**cmd;
	char	*envp;
	int		childs;
	int		infile;
	int		outfile;
	int		status;
}t_pipex;

// child.c

void	childs(t_pipex *pipex, int index, char *str, char **envp);
void	check_access(t_pipex *pipex, char *cmd_str);
void	dup2_function(int read, int write);
void	find_path(t_pipex *pipex, char **envp);
char	*get_path(t_pipex *pipex, char *cmd);

// pipe.c

void	create_pipe(t_pipex *pipex);
void	destroy_pipe(t_pipex *pipex);
void	alloc_pipe(t_pipex *pipex);
void	ft_free(t_pipex *pipex);

// error.c

void	throw_error(char *str);
void	throw_error2(char *str);
void	throw_error3(char *str);

void	ft_close(t_pipex *pipex);

#endif