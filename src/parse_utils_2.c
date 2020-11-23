/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 09:15:00 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/23 13:42:40 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	is_wspace(const char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' \
			|| c == ' ');
}

static void	validate(char *str)
{
	if (*str != '\0')
		handle_error("Failed to parse the figures");
}

static long	set_number(char *str)
{
	long	nb;

	nb = 0;
	while (ft_isdigit(*str))
		nb = nb * 10 + (*str++ - '0');
	validate(str);
	return (nb);
}

int			ft_atoi(char *str)
{
	int		sign;

	sign = 1;
	while (is_wspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	return ((int)(sign * set_number(str)));
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
	validate(str);
	return (ret * div);
}
