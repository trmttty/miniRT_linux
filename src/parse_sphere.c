/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 01:27:28 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/23 04:43:58 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_sphere(t_rt *rt)
{
	t_sp	*sp;
	t_obj	*obj;
	t_list	*element;

	if (!(sp = ft_calloc(1, sizeof(t_sp))))
		handle_perror("Failed to calloc sphere");
	if (!(obj = ft_calloc(1, sizeof(t_obj))))
		handle_perror("Failed to calloc sphere object");
	if (!(element = ft_lstnew(obj)))
		handle_perror("Failed to lstnew obj");
	ft_lstadd_back(&rt->obj_lst, element);
	if (tabsize(rt->tab) != 4)
		handle_error("Failed to parse sp");
	sp->sc = parse_vector(rt->tab[1]);
	sp->diameter = ft_atof(rt->tab[2]);
	sp->color = parse_color(rt->tab[3]);
	obj->shape.sp = sp;
	obj->type = SPHERE;
	obj->col = sp->color;
	ft_tabfree(rt->tab);
	rt->tab = NULL;
}
