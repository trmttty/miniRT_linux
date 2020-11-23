/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 07:09:47 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/23 12:19:11 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int			main(int argc, char *argv[])
{
	t_rt	rt;

	ft_memset(&rt, 0, sizeof(t_rt));
	parse_rt(argc, argv, &rt);
	create_img(&rt);
	put_img(&rt);
	return (0);
}
