/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:13:13 by dgross            #+#    #+#             */
/*   Updated: 2022/10/22 13:36:13 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdlib.h> // exit
#include <stdio.h> // perror

void	throw_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	throw_error2(char *str)
{
	perror(str);
	exit(EXIT_SUCCESS);
}

void	throw_error3(char *str)
{
	perror(str);
}
