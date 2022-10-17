/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:26:19 by dgross            #+#    #+#             */
/*   Updated: 2022/10/17 17:07:55 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipex
{
	int		**pipe;
	int		fd[2];
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
void	dup2_function(int read, int write);
void	find_path(t_pipex *pipex, char **envp);
char	*get_path(t_pipex *pipex, char *cmd);

// pipe.c

void	create_pipe(t_pipex *pipex);
void	destroy_pipe(t_pipex *pipex);
void	alloc_pipe(t_pipex *pipex);

// error.c

void	throw_error(char *str);
void	throw_error2(char *str);

// here_doc.c

void	check_heredoc(t_pipex *pipex, int argc, char **argv);

void	check_access(t_pipex *pipex, char *cmd_str);

#endif