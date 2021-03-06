/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:35:27 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/23 04:43:35 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		parse_cylinder(t_rt *rt)
{
	t_cy	*cy;
	t_obj	*obj;

	if (!(cy = ft_calloc(1, sizeof(t_cy))))
		handle_perror("Failed to calloc cylinder");
	if (!(obj = ft_calloc(1, sizeof(t_obj))))
		handle_perror("Failed to calloc cylinder object");
	if (tabsize(rt->tab) != 6)
		handle_error("Failed to parse cy");
	cy->bottom = parse_vector(rt->tab[1]);
	cy->normal = parse_vector(rt->tab[2]);
	normalize(&cy->normal);
	cy->col = parse_color(rt->tab[3]);
	cy->diameter = ft_atof(rt->tab[4]);
	cy->height = ft_atof(rt->tab[5]);
	cy->top = add(cy->bottom, multi(cy->normal, cy->height));
	cy->inside = 0;
	obj->shape.cy = cy;
	obj->type = CYLINDER;
	obj->col = cy->col;
	ft_tabfree(rt->tab);
	ft_lstadd_back(&rt->obj_lst, ft_lstnew(obj));
}
