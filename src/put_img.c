/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:27:15 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/22 19:28:38 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	exit_minirt()
{
	exit(EXIT_SUCCESS);
}

static int	next_camera(int keycode, t_rt *rt)
{
	if (keycode == KEY_ESC)
	{
		exit(EXIT_SUCCESS);
	}
	if (keycode == KEY_TAB)
	{
		rt->cam_crrnt = rt->cam_crrnt->next;
		if (!rt->cam_crrnt)
			rt->cam_crrnt = rt->cam_lst;
		rt->cam = (t_camera*)(rt->cam_crrnt->content);
		mlx_clear_window(rt->mlx, rt->win);
		mlx_put_image_to_window(rt->mlx, rt->win, rt->cam->img.img, 0, 0);
	}
	return (0);
}

static int	focus_in(t_rt *rt)
{
	mlx_clear_window(rt->mlx, rt->win);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->cam->img.img, 0, 0);
	return (0);
}

void		put_img(t_rt *rt)
{
	rt->cam_crrnt = rt->cam_lst;
	rt->cam = (t_camera*)(rt->cam_crrnt->content);
	if (rt->save)
		create_bmp(rt);
	else
	{
		mlx_put_image_to_window(rt->mlx, rt->win, rt->cam->img.img, 0, 0);
		mlx_hook(rt->win, 2, 1L << 0, next_camera, rt);
		mlx_hook(rt->win, 17, 1L << 17, exit_minirt, rt);
		mlx_hook(rt->win, 9, 1L << 21, focus_in, rt);
		mlx_loop(rt->mlx);
	}
}
