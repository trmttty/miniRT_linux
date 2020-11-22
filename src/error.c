/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 23:04:48 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/22 19:34:47 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	handle_error(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	handle_perror(char *message)
{
	ft_putstr_fd("Error\n", 2);
	perror(message);
	exit(1);
}
