/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub3d.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:08:34 by mrochet           #+#    #+#             */
/*   Updated: 2021/04/29 16:20:17 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_CUB3D_H
# define PARSE_CUB3D_H

typedef struct s_res
{
	int			x;	
	int			y;
}				t_res;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct s_path
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*S;
}				t_path;

typedef struct s_map
{
	int			user_x;
	int			user_y;
	int			user_deg;
}				t_map;

typedef struct s_parse
{
	t_res		res;
	t_rgb		f;
	t_rgb		c;
	t_path		path;
	t_map		map;
	int			error;
	char		*file;
	char		*file_map;
	int			ind;
}				t_parse;

void		ft_free_split(char **tab);
size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *s, int c);
char		*ft_strfjoin(char *s1, char *s2);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);

void 		init_t_parse(t_parse *stock);
void		print_struct(t_parse stock);
char		*read_file(char *fichier);
int			parsing(char *name_file, t_parse *stock);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			analyse_file(char *file, t_parse *parse);
int			verif_name(char *namefile, t_parse *stock);
int			print_err(char *mssg_err, t_parse *stock);
int			print_f_err(char *mssg_err, void *test, t_parse *stock);

int			verif_r(char *str, t_parse *stock);
void		parse_r(char *file_r, t_parse *stock);
int			verif_fc(char *str, t_parse *stock);
void		parse_fc(char *file_fc, t_parse *stock);
void		parse_path(char *file_path, t_parse *stock);
char		*verif_path(char *str, t_parse *stock);
void		redirect(char *file, t_parse *stock);

int			init_map(char *file, t_parse *stock);
int			find_map(char *file, t_parse *stock);
int			parse_map(t_parse *stock);
int			find_user(char **tab, t_parse *stock);
#endif
