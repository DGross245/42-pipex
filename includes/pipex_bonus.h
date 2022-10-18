/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:21:14 by dgross            #+#    #+#             */
/*   Updated: 2022/10/18 14:14:46 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

typedef struct s_pipex
{
	int		here_doc;
	int		**pipe;
	int		pid;
	char	**path;
	char	*file;
	char	**cmd;
	char	*envp;
	int		childs;
	int		infile;
	int		outfile;
	char	*limiter;
}t_pipex;

// child.c

void	childs(t_pipex *pipex, int index, char *str, char **envp);
void	check_access(t_pipex *pipex, char *cmd_str);
void	dup2_function(int read, int write);
void	find_path(t_pipex *pipex, char **envp);
char	*get_path(t_pipex *pipex, char *cmd);

// pipe.c

void	create_pipe(t_pipex *pipex, char **argv, int argc);
void	destroy_pipe(t_pipex *pipex);
void	alloc_pipe(t_pipex *pipex);
void	ft_free(t_pipex *pipex);

// error.c

void	throw_error(char *str);
void	throw_error2(char *str);

// here_doc.c

void	check_heredoc(t_pipex *pipex, int argc, char **argv);
void	ft_here_doc(t_pipex *pipex);
void	write_pipes(t_pipex *pipex);

#endif