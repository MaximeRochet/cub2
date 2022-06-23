/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:06:05 by mrochet           #+#    #+#             */
/*   Updated: 2022/06/01 12:07:06 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_position(t_cub *cub)
{
	double	dir;

	cub->player.angle += 0.034 * cub->keys.l_arrow - 0.034 * cub->keys.r_arrow;
	cub->player.angle += 2 * PI * (cub->player.angle < 0)
		- 2 * PI * (cub->player.angle > 2 * PI);
	dir = 0.05 * (cos(cub->player.angle) * (cub->keys.w - cub->keys.s)
			+ cos(cub->player.angle - PI / 2) * (cub->keys.d - cub->keys.a));
	if (cub->parser->map[(int)cub->player.y][(int)(cub->player.x + dir + 0.01
		* (dir > 0) - 0.01 * (dir < 0))] != '1')
		cub->player.x += dir;
	dir = 0.05 * (sin(cub->player.angle) * (cub->keys.w - cub->keys.s)
			+ sin(cub->player.angle - PI / 2) * (cub->keys.d - cub->keys.a));
	if (cub->parser->map[(int)(cub->player.y - dir - 0.01 * (dir > 0) + 0.01
			* (dir < 0))][(int)cub->player.x] != '1')
		cub->player.y -= dir;
}

void	get_dir(t_cub *cub, t_parser *parser)
{
	int	i;
	if (cub->parser->spawndir == 'N')
		cub->player.angle = PI / 2;
	else if (cub->parser->spawndir == 'S')
		cub->player.angle = 3 * PI / 2;
	else if (cub->parser->spawndir == 'E')
		cub->player.angle = 0;
	else
		cub->player.angle = PI;
	i = -1;
	while (++i < 4)
	{
		cub->text[i].img = mlx_xpm_file_to_image(cub->mlx, cub->parser->text[i],
				&cub->text[i].width, &cub->text[i].height);
		if(!(cub->text[i].img))
		{
			printf("Texture incorrecte");
			exit(0);
		}
			cub->text[i].addr = mlx_get_data_addr(cub->text[i].img,
				&cub->text[i].bpp, &cub->text[i].linelength,
				&cub->text[i].endian);
	}
}

void	init_cub(t_cub *cub, t_parser *parser)
{

	cub->parser = parser;
	cub->player.x = cub->parser->spawnx + 0.5;
	cub->player.y = cub->parser->spawny + 0.5;
	ft_bzero(&cub->keys, sizeof(t_keys));
	cub->imgtoprint = 0;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, XMAX, YMAX, "cub3D");
	cub->img1.img = mlx_new_image(cub->mlx, XMAX, YMAX);
	cub->img1.addr = mlx_get_data_addr(cub->img1.img, &cub->img1.bpp,
			&cub->img1.linelength, &cub->img1.endian);
	cub->img2.img = mlx_new_image(cub->mlx, XMAX, YMAX);
	cub->img2.addr = mlx_get_data_addr(cub->img2.img, &cub->img2.bpp,
			&cub->img2.linelength, &cub->img2.endian);
	get_dir(cub, parser);
}

int	run(t_parser *parser)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	if (!cub)
		print_err("Error malloc", parser);
	init_cub(cub, parser);
	mlx_hook(cub->win, 17, (1L << 17), free_all_exit, cub);
	mlx_hook(cub->win, 2, (1L << 0), keypress, cub);
	mlx_hook(cub->win, 3, (1L << 1), keyrelease, cub);
	mlx_loop_hook(cub->mlx, draw, cub);
	mlx_loop(cub->mlx);
	return (1);
}
