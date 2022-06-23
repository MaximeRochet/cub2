/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:05:07 by mrochet           #+#    #+#             */
/*   Updated: 2022/05/31 13:05:10 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_cub *cub, t_img img, t_ray ray, t_wall wall)
{
	double	y;
	int		i;
	int		win_x;
	int		win_y;
	int		*addr[2];

	i = -1;
	if (wall.side == EAST || wall.side == WEST)
		win_x = (int)(ray.ver_y * cub->text[wall.side].width)
			% cub->text[wall.side].width;
	else
		win_x = (int)(ray.hor_x * cub->text[wall.side].width)
			% cub->text[wall.side].width;
	win_y = YMAX / 2 - wall.height / 2;
	addr[0] = img.addr;
	addr[1] = cub->text[wall.side].addr;
	y = (double)cub->text[wall.side].height / wall.height;
	while (++i < wall.height)
	{
		if (win_y + i >= 0 && win_y + i < YMAX && y >= 0 && y
			< cub->text[wall.side].height)
			addr[0][(win_y + i) * XMAX + (XMAX - ray.ray_nb)]
				= addr[1][(int)y * cub->text[wall.side].width + win_x];
		y += (double)cub->text[wall.side].height / wall.height;
	}
}

void	draw_ray(t_cub *cub, t_img img, t_ray ray)
{
	t_wall	wall;

	if (ray.ver_dist <= ray.hor_dist)
	{
		if (ray.angle > PI / 2 && ray.angle < 3 * PI / 2)
			wall.side = WEST;
		else
			wall.side = EAST;
		ray.hor_dist = ray.ver_dist;
	}
	else
	{
		if (ray.angle > 0 && ray.angle < PI)
			wall.side = NORTH;
		else
			wall.side = SOUTH;
	}
	wall.height = (int)YMAX / (ray.hor_dist
			* cos(cub->player.angle - ray.angle));
	draw_wall(cub, img, ray, wall);
}

void	floor_ceiling(t_cub *cub, t_img img)
{
	int	i;
	int	j;

	i = 0;
	while (i < YMAX)
	{
		j = 0;
		while (j < XMAX)
		{
			if (i < YMAX / 2)
				put_pixel(img, j, i, cub->parser->c);
			else
				put_pixel(img, j, i, cub->parser->f);
			j++;
		}
		i++;
	}
}

int	draw(t_cub *cub)
{
	player_position(cub);
	if (!cub->imgtoprint)
	{
		floor_ceiling(cub, cub->img1);
		raycast(cub, cub->img1);
		cub->imgtoprint = 1;
		mlx_put_image_to_window(cub->mlx, cub->win, cub->img1.img, 0, 0);
	}
	else
	{
		floor_ceiling(cub, cub->img2);
		raycast(cub, cub->img2);
		cub->imgtoprint = 0;
		mlx_put_image_to_window(cub->mlx, cub->win, cub->img2.img, 0, 0);
	}
	usleep(150);
	return (1);
}
