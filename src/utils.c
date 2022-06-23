/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:06:17 by mrochet           #+#    #+#             */
/*   Updated: 2022/05/31 16:18:15 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img img, int x, int y, int color)
{
	char	*tmp;

	tmp = img.addr + y * img.linelength + x * (img.bpp / 8);
	*(int *)tmp = color;
}

int	keypress(int keycode, t_cub *cub)
{
	if (keycode == ESC)
		free_all_exit(cub);
	if (keycode == W)
		cub->keys.w = 1;
	if (keycode == A)
		cub->keys.a = 1;
	if (keycode == S)
		cub->keys.s = 1;
	if (keycode == D)
		cub->keys.d = 1;
	if (keycode == L_ARROW)
		cub->keys.l_arrow = 1;
	if (keycode == R_ARROW)
		cub->keys.r_arrow = 1;
	return (1);
}

int	keyrelease(int keycode, t_cub *cub)
{
	if (keycode == W)
		cub->keys.w = 0;
	if (keycode == A)
		cub->keys.a = 0;
	if (keycode == S)
		cub->keys.s = 0;
	if (keycode == D)
		cub->keys.d = 0;
	if (keycode == L_ARROW)
		cub->keys.l_arrow = 0;
	if (keycode == R_ARROW)
		cub->keys.r_arrow = 0;
	return (1);
}

int	free_all_exit(t_cub *cub)
{
	int	i;

	i = 0;
	free_parser(cub->parser);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_image(cub->mlx, cub->img1.img);
	mlx_destroy_image(cub->mlx, cub->img2.img);
	while (i < 4)
	{
		mlx_destroy_image(cub->mlx, cub->text[i].img);
		i++;
	}
	free(cub);
	exit(0);
}
