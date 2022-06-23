/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:05:47 by mrochet           #+#    #+#             */
/*   Updated: 2022/05/31 13:05:50 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_vertical(t_cub *cub, t_ray *ray)
{
	if (ray->dir_x < 0.001 && ray->dir_x > -0.001)
		ray->dir_x = 0;
	if (ray->dir_y < 0.001 && ray->dir_y > -0.001)
		ray->dir_y = 0;
	ray->cast_dist = 0;
	ray->r_tan = tan(ray->angle);
	if (ray->dir_x > 0)
	{
		ray->ver_x = (int)cub->player.x + 1;
		ray->ver_y = (cub->player.x - ray->ver_x) * ray->r_tan + cub->player.y;
		ray->x_offset = 1;
	}
	else if (ray->dir_x < 0)
	{
		ray->ver_x = (int)cub->player.x - 0.00001;
		ray->ver_y = (cub->player.x - ray->ver_x) * ray->r_tan + cub->player.y;
		ray->x_offset = -1;
	}
	else
	{
		ray->ver_x = cub->player.x;
		ray->ver_y = cub->player.y;
		ray->cast_dist = 1000;
	}
	ray->y_offset = -ray->x_offset * ray->r_tan;
}

static void	cast_vertical(t_cub *cub, t_ray *ray)
{
	while (ray->cast_dist < 1000)
	{
		ray->x_decal = (int)ray->ver_x;
		ray->y_decal = (int)ray->ver_y;
		if (ray->x_decal >= 0 && ray->x_decal < cub->parser->linelength
			&& ray->y_decal >= 0 && ray->y_decal < cub->parser->linenb
			&& cub->parser->map[ray->y_decal][ray->x_decal] == '1')
		{
			ray->cast_dist = 1000;
			ray->ver_dist = (float)(ray->dir_x * (ray->ver_x - cub->player.x)
					+ ray->dir_y * (ray->ver_y - cub->player.y));
		}
		else
		{
			ray->ver_x += ray->x_offset;
			ray->ver_y += ray->y_offset;
			ray->cast_dist++;
		}
	}
}

static void	init_horizontal(t_cub *cub, t_ray *ray)
{
	ray->cast_dist = 0;
	if (ray->r_tan == 0)
		ray->r_tan = 1;
	else
		ray->r_tan = 1.0 / ray->r_tan;
	if (ray->dir_y > 0)
	{
		ray->hor_y = (int)cub->player.y + 1;
		ray->hor_x = (cub->player.y - ray->hor_y) * ray->r_tan + cub->player.x;
		ray->y_offset = 1;
		ray->x_offset = -ray->y_offset * ray->r_tan;
	}
	else if (ray->dir_y < 0)
	{
		ray->hor_y = (int)cub->player.y - 0.00001;
		ray->hor_x = (cub->player.y - ray->hor_y) * ray->r_tan + cub->player.x;
		ray->y_offset = -1;
		ray->x_offset = -ray->y_offset * ray->r_tan;
	}
	else
	{
		ray->hor_y = cub->player.y;
		ray->hor_x = cub->player.x;
		ray->cast_dist = 1000;
	}
}

static void	cast_horizontal(t_cub *cub, t_ray *ray)
{
	while (ray->cast_dist < 1000)
	{
		ray->y_decal = (int)ray->hor_y;
		ray->x_decal = (int)ray->hor_x;
		if (ray->y_decal >= 0 && ray->x_decal < cub->parser->linelength
			&& ray->x_decal >= 0 && ray->y_decal < cub->parser->linenb
			&& cub->parser->map[ray->y_decal][ray->x_decal] == '1')
		{
			ray->cast_dist = 1000;
			ray->hor_dist = (float)(ray->dir_x * (ray->hor_x - cub->player.x)
					+ ray->dir_y * (ray->hor_y - cub->player.y));
		}
		else
		{
			ray->hor_x += ray->x_offset;
			ray->hor_y += ray->y_offset;
			ray->cast_dist++;
		}
	}
}

void	raycast(t_cub *cub, t_img img)
{
	t_ray	ray;

	ray.ray_nb = 0;
	while (ray.ray_nb < XMAX)
	{
		ray.angle = cub->player.angle - PI / 4 + ray.ray_nb * PI / 2 / XMAX;
		ray.angle += 2 * PI * (ray.angle < 0) - 2 * PI * (ray.angle > 2 * PI);
		ray.dir_x = cos(ray.angle);
		ray.dir_y = -sin(ray.angle);
		init_vertical(cub, &ray);
		ray.ver_dist = 100000;
		ray.hor_dist = 100000;
		cast_vertical(cub, &ray);
		init_horizontal(cub, &ray);
		cast_horizontal(cub, &ray);
		draw_ray(cub, img, ray);
		ray.ray_nb++;
	}
}
