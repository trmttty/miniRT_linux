/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 22:45:45 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/22 19:48:58 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	parse_line(t_rt *rt)
{
	if (!(rt->tab = ft_split(rt->line, ' ')))
		handle_perror("Failed split line");
	if (ft_strncmp(*rt->tab, "R", 2) == 0)
		return (parse_resolution(rt));
	else if (ft_strncmp(*rt->tab, "A", 2) == 0)
		return (parse_ambient(rt));
	else if (ft_strncmp(*rt->tab, "l", 2) == 0)
		return (parse_light(rt));
	else if (ft_strncmp(*rt->tab, "sp", 3) == 0)
		return (parse_sphere(rt));
	else if (ft_strncmp(*rt->tab, "pl", 3) == 0)
		return (parse_plane(rt));
	else if (ft_strncmp(*rt->tab, "sq", 3) == 0)
		return (parse_square(rt));
	else if (ft_strncmp(*rt->tab, "cy", 3) == 0)
		return (parse_cylinder(rt));
	else if (ft_strncmp(*rt->tab, "tr", 3) == 0)
		return (parse_triangle(rt));
	else if (ft_strncmp(*rt->tab, "c", 2) == 0)
		return (parse_camera(rt));
	handle_error("Invalid type identifier");
}

void		check_argument(int argc, char **argv, t_rt *rt)
{
	if (!(argc == 2 || (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)))
		handle_argument_error("Invalid arguments");
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", 4))
		handle_argument_error("Invalid file extension");
	if (argc == 3)
		rt->save = 1;
}

void		parse_rt(int argc, char **argv, t_rt *rt)
{
	int		fd;
	int		rv;

	check_argument(argc, argv, rt);
	if (!(rt->mlx = mlx_init()))
		handle_error("Failed to initialize Minilibx");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		handle_perror("Failed to open scene file");
	while ((rv = get_next_line(fd, &(rt->line))) > 0)
	{
		if (ft_isalpha(*(rt->line)))
			parse_line(rt);
		free(rt->line);
		rt->line = NULL;
	}
	if (ft_isalpha(*(rt->line)))
		parse_line(rt);
	free(rt->line);
	rt->line = NULL;
	if (close(fd) == -1)
		handle_perror("Failed close file");
	if (rt->res.read == 0)
		handle_perror("Resolution must be declared");
	if (rt->cam_lst == NULL)
		handle_perror("Camera must be declared");
}
