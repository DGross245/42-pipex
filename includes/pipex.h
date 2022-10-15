/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:26:19 by dgross            #+#    #+#             */
/*   Updated: 2022/10/15 13:12:36 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipex
{
	int		**pipe;
	char	**path;
	char	*file;
	char	**cmd;
	char	*envp;
	int		childs;
	int		infile;
	int		outfile;
}t_pipex;

#endif