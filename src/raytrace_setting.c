/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_setting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 13:42:49 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/12 11:28:42 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

void	my_mlx_pixel_put(t_myimg *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	set_ray(t_rt *rt, t_raytrace *r)
{
	rt->cam->up = vectornew(0, 1, 0);
	if (norm(cross(rt->cam->up, rt->cam->orient)) == 0)
		rt->cam->up = vectornew(0, 0, 1);
	r->dx = cross(rt->cam->up, rt->cam->orient);
	normalize(&r->dx);
	r->dy = cross(rt->cam->orient, r->dx);
	normalize(&r->dy);
}

void	calc_ray(t_rt *rt, t_raytrace *r, int x, int y)
{
	t_calc_ray	cr;
	int			w;
	int			h;

	set_ray(rt, r);
	w = rt->res.x;
	h = rt->res.y;
	if (w >= h)
		cr.w_s = 2;
	else
		cr.w_s = (2 * w) / (float)h;
	if (w <= h)
		cr.h_s = 2;
	else
		cr.h_s = (2 * h) / (float)w;
	cr.pc_x = (cr.w_s * (float)x) / (float)(w - 1) - cr.w_s / 2.0f;
	cr.pc_y = (-cr.h_s * (float)y) / (float)(h - 1) + cr.h_s / 2.0f;
	cr.dist = (cr.w_s / 2.0f) / tan((rt->cam->fov / 2.0f) * (M_PI / 180.0f));
	cr.v = add(rt->cam->vp, multi(rt->cam->orient, cr.dist));
	cr.v = add(cr.v, multi(r->dx, cr.pc_x));
	cr.v = add(cr.v, multi(r->dy, cr.pc_y));
	r->eye_ray.start = rt->cam->vp;
	r->eye_ray.dir = sub(cr.v, rt->cam->vp);
	normalize(&r->eye_ray.dir);
}

void	set_raytrace(t_rt *rt)
{
	t_raytrace		r;
	int				x;
	int				y;

	ft_memset(&r, 0, sizeof(r));
	y = 0;
	while (y < rt->res.y)
	{
		x = 0;
		while (x < rt->res.x)
		{
			calc_ray(rt, &r, x, y);
			raytrace(rt, &r);
			my_mlx_pixel_put(&rt->cam->img, x, y, convert_colorf(r.col));
			x++;
		}
		y++;
	}
}
