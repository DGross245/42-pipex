/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgross <dgross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:52:07 by dgross            #+#    #+#             */
/*   Updated: 2022/10/17 17:09:21 by dgross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h> // exit
#include <stdio.h> // perror
#include <unistd.h> // perror

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
