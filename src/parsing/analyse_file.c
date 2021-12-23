/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:34:30 by mrochet           #+#    #+#             */
/*   Updated: 2021/04/22 17:32:46 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*verif_path(char *str, t_parse *stock)
{
	char	*charset;
	int		fd;

	charset = "NSOWEA ";
	while (ft_strchr(charset, *str))
		str++;
	//a decommenter quand les fichier seront valides
	/*fd = open(str, O_RDONLY);
	  if(fd == -1)
	  return(print_err("Un chemin est incorrect"));
	  close(fd);*/
	return (str);
}

void	parse_path(char *file_path, t_parse *stock)
{
	char	*path;

	path = verif_path(file_path, stock);
	if (!path)
		return ;
	if (file_path[0] == 'N' && stock->path.NO == NULL)
		stock->path.NO = ft_strdup(path);
	if (file_path[0] == 'S' && file_path[1] == 'O' && stock->path.SO == NULL)
		stock->path.SO = ft_strdup(path);
	if (file_path[0] == 'W' && stock->path.WE == NULL)
		stock->path.WE = ft_strdup(path);
	if (file_path[0] == 'E' && stock->path.EA == NULL)
		stock->path.EA = ft_strdup(path);
	if (file_path[0] == 'S' && stock->path.S == NULL)
		stock->path.S = ft_strdup(path);
	stock->ind += 100;
}

void	redirect(char *file, t_parse *stock)
{
	char	*charset;
	charset = "SNWE";
	if (file[0] == 'R')
		parse_r(file, stock);
	else if (ft_strchr(charset, file[0]))
		parse_path(file, stock);
	else if (file[0] == 'F')
		parse_fc(file, stock);
	else if (file[0] == 'C')
		parse_fc(file, stock);
}

int	analyse_file(char *file, t_parse *stock)
{
	char	**tab;
	int		i;
	int		y;

	i = -1;
	y = 0;
	tab = ft_split(file, 10);
	while (tab[++i])
	{
		y = 0;
		while (tab[i][y] <= 32)
			y++;
		if (strchr("RNSWESFC", tab[i][y]))
			redirect(tab[i] + y, stock);
		else if (!strchr("1 02NEWS\n", tab[i][y]))
			return (print_err("Ligne incorrect dans le .cub", stock));
		if (stock->error == 1)
			return (0);
	}
	ft_free_split(tab);
	return (init_map(file, stock));
}
