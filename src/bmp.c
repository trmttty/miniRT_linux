/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttarumot <ttarumot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:29:04 by ttarumot          #+#    #+#             */
/*   Updated: 2020/11/13 12:31:22 by ttarumot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	fill_bmp(char **data, t_rt *rt)
{
	int i;
	int j;
	int k;
	int x;
	int y;

	i = HEADER_SIZE;
	y = rt->res.y;
	while (y--)
	{
		x = -1;
		while (++x < rt->res.x)
		{
			j = (x * (rt->cam->img.bits_per_pixel / 8)) + \
				(y * rt->cam->img.line_length);
			*(*data + i++) = *(rt->cam->img.addr + j++);
			*(*data + i++) = *(rt->cam->img.addr + j++);
			*(*data + i++) = *(rt->cam->img.addr + j);
		}
		k = 0;
		while (k++ < (4 - (rt->res.x * 3) % 4) % 4)
			*(*data + i++) = 0;
	}
}

void	header_bmp(char **data, t_rt *rt)
{
	unsigned int filesize;
	unsigned int padding;

	padding = (4 - (rt->res.x * 3) % 4) % 4;
	filesize = HEADER_SIZE + (3 * rt->res.x + padding) * rt->res.y;
	*(unsigned char *)*data = 'B';
	*(unsigned char *)(*data + 1) = 'M';
	*(unsigned int *)(*data + 2) = filesize;
	*(unsigned int *)(*data + 6) = 0u;
	*(unsigned int *)(*data + 10) = HEADER_SIZE;
	*(unsigned int *)(*data + 14) = HEADER_SIZE - 14;
	*(int *)(*data + 18) = rt->res.x;
	*(int *)(*data + 22) = rt->res.y;
	*(unsigned short *)(*data + 26) = 1;
	*(unsigned short *)(*data + 28) = 24;
}

void	export_bmp(char *filename, t_rt *rt)
{
	int				fd;
	unsigned int	filesize;
	unsigned int	padding;
	char			*data;

	padding = (4 - (rt->res.x * 3) % 4) % 4;
	filesize = HEADER_SIZE + (3 * rt->res.x + padding) * rt->res.y;
	if (!(data = malloc((filesize))))
		handle_perror("Failed to malloc bmp data", rt);
	ft_memset(data, 0, filesize);
	header_bmp(&data, rt);
	fill_bmp(&data, rt);
	if ((fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		handle_perror("Failed to read bmp file", rt);
	write(fd, data, (filesize));
	free(data);
	close(fd);
}

void	create_bmp(t_rt *rt)
{
	t_list	*tmp;
	char	*filename;
	char	*index_str;
	int		index;

	index = 1;
	tmp = rt->cam_lst;
	while (tmp)
	{
		rt->cam = (t_camera*)(tmp->content);
		if (!(index_str = ft_itoa(index)))
			handle_perror("Failed to create index_str", rt);
		if (!(filename = ft_strjoin(index_str, ".bmp")))
			handle_perror("Failed to create filename", rt);
		export_bmp(filename, rt);
		free(index_str);
		free(filename);
		index++;
		tmp = tmp->next;
	}
}
