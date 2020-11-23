/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 09:16:25 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/23 12:16:13 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_wspace(const char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' \
			|| c == ' ');
}

double		ft_atof(char *str)
{
	double	ret;
	double	div;
	int		sign;

	while (is_wspace(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	ret = 0;
	while (ft_isdigit(*str))
		ret = ret * 10 + sign * (*str++ - '0');
	div = 1;
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			ret = ret * 10 + sign * (*str++ - '0');
			div /= 10;
		}
	}
	return (ret * div);
}
