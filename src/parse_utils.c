/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 09:15:00 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/22 19:47:44 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

size_t		tabsize(char **tab)
{
	size_t	size;

	size = 0;
	if (!tab)
		return (size);
	while (*tab)
	{
		size++;
		tab++;
	}
	return (size);
}

static void	check_color(size_t size, char **rgb, t_rt *rt)
{
	int n;

	while (size--)
	{
		if (ft_strlen(rgb[size]) > 3)
		{
			ft_tabfree(rgb);
			handle_error("RGB colors in range [0-255]");
		}
		n = ft_atoi(rgb[size]);
		if (n < 0 || n > 255)
		{
			ft_tabfree(rgb);
			handle_error( "RGB colors in range [0-255]");
		}
	}
}

t_colorf	parse_color(char *s, t_rt *rt)
{
	t_colorf	c;
	char		**rgb;
	size_t		size;

	if (!(rgb = ft_split(s, ',')))
		handle_perror("Failed to split color");
	size = tabsize(rgb);
	if (size != 3)
	{
		ft_tabfree(rgb);
		handle_error("Failed to parse color");
	}
	check_color(size, rgb, rt);
	c.r = ft_atoi(rgb[0]) / 255.0f;
	c.g = ft_atoi(rgb[1]) / 255.0f;
	c.b = ft_atoi(rgb[2]) / 255.0f;
	ft_tabfree(rgb);
	return (c);
}

t_vector	parse_vector(char *s, t_rt *rt)
{
	t_vector	v;
	char		**vec3;

	if (!(vec3 = ft_split(s, ',')))
		handle_perror("Failed split vector");
	if (tabsize(vec3) != 3)
	{
		ft_tabfree(vec3);
		handle_error("Failed parse vector");
	}
	v.x = ft_atof(vec3[0]);
	v.y = ft_atof(vec3[1]);
	v.z = ft_atof(vec3[2]);
	ft_tabfree(vec3);
	return (v);
}

t_vector	parse_normal(char *s, t_rt *rt)
{
	t_vector	normal;

	normal = parse_vector(s, rt);
	if (normal.x < -1 || normal.x > 1)
		handle_error("Normalized orientation vector in range [-1,1]");
	if (normal.y < -1 || normal.y > 1)
		handle_error("Normalized orientation vector in range [-1,1]");
	if (normal.z < -1 || normal.z > 1)
		handle_error("Normalized orientation vector in range [-1,1]");
	return (normal);
}
