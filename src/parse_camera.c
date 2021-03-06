/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:57:53 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/23 04:42:32 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_camera(t_rt *rt)
{
	t_camera	*cam;
	t_list		*element;

	if (!(cam = ft_calloc(1, sizeof(t_camera))))
		handle_perror("Failed to calloc camera");
	if (!(element = ft_lstnew(cam)))
		handle_perror("Failed to lstnew light");
	ft_lstadd_back(&rt->cam_lst, element);
	if (tabsize(rt->tab) != 4)
		handle_error("Failed to parse c");
	cam->vp = parse_vector(rt->tab[1]);
	cam->orient = parse_normal(rt->tab[2]);
	normalize(&cam->orient);
	if (dot(cam->orient, cam->orient) > 1)
		handle_error("Orientation vector in range [-1,1]");
	cam->fov = ft_atoi(rt->tab[3]);
	if (cam->fov < 0 || cam->fov > 180)
		handle_error("FOV in range [0,180]");
	ft_tabfree(rt->tab);
	rt->tab = NULL;
}
