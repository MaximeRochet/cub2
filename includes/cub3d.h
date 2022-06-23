/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:04:19 by mrochet           #+#    #+#             */
/*   Updated: 2022/05/31 16:18:44 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "keys.h"

# define YMAX 1080
# define XMAX 1920

# define PI 3.14159265

typedef enum e_texture
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}			t_texture;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	angle;
	double	r_tan;
	double	ver_x;
	double	ver_y;
	double	hor_x;
	double	hor_y;
	double	x_offset;
	double	y_offset;
	int		x_decal;
	int		y_decal;
	int		cast_dist;
	double	hor_dist;
	double	ver_dist;
	int		ray_nb;
}				t_ray;

typedef struct s_wall
{
	t_texture	side;
	int			height;
}				t_wall;

typedef struct s_parser
{
	char	*text[4];
	int		f;
	int		c;
	char	*full_file;
	char	**map;
	int		linelength;
	int		linenb;
	int		spawnx;
	int		spawny;
	char	spawndir;
	int		ind;
}				t_parser;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	l_arrow;
	bool	r_arrow;
}				t_keys;

typedef struct s_img
{
	void	*img;
	void	*addr;
	int		bpp;
	int		linelength;
	int		endian;
}				t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}				t_player;

typedef struct s_text
{
	void	*img;
	void	*addr;
	int		bpp;
	int		linelength;
	int		endian;
	int		width;
	int		height;
}				t_text;

typedef struct s_cub
{
	t_parser	*parser;
	void		*mlx;
	void		*win;
	t_img		img1;
	t_img		img2;
	t_player	player;
	bool		imgtoprint;
	t_keys		keys;
	t_text		text[4];
}				t_cub;

/* PARSING */

int		parsing(char *file, t_parser *parser);
void	analyse_file(t_parser*parser);
char	*verif_path(char *str, t_parser *parser);
void	parse_fc(char *file_fc, t_parser *parser);
int		analyse_map(t_parser *parser);
void	free_parser(t_parser *parser);

/* RUN.C */

int		run(t_parser *data);
void	player_position(t_cub *cub);

/* RAYCASTER.C */

void	raycast(t_cub *cub, t_img img);

/* DRAW.C */

int		draw(t_cub *cub);
void	draw_ray(t_cub *cub, t_img img, t_ray ray);

/* UTILS.C */

void	put_pixel(t_img img, int x, int y, int color);
int		keypress(int keycode, t_cub *cub);
int		keyrelease(int keycode, t_cub *cub);
int		free_all_exit(t_cub *cub);
void	print_struct(t_parser *parser);
int		print_err(char *mssg_err, t_parser *parser);
int		color(int r, int g, int b);
void	ft_free_split(char **tab);

#endif
