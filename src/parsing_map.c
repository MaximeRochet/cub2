/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:15:29 by mrochet           #+#    #+#             */
/*   Updated: 2022/05/31 15:07:44 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	find_user(char **tab, t_parser *parser)
{
	int	i;
	int	y;

	i = -1;
	y = -1;
	while (tab[++i])
	{
		while (tab[i][++y])
		{
			if (!strchr("01 \tNSEW", tab[i][y]))
				print_err("map invalide", parser);
			if (strchr("NSEW", tab[i][y]) && parser->spawnx == -1)
			{
				parser->spawnx = y;
				parser->spawny = i;
				parser->spawndir = tab[i][y];
				tab[i][y] = '0';
			}
			else if (strchr("NSEW", tab[i][y]) && parser->spawnx != 0)
				print_err("position multiple", parser);
		}
		y = -1;
	}
	return (1);
}

int	close_map(char **tab, int x, int y, t_parser *parser)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	if (ft_strchr("NSEW0", tab[y][x]))
	{
		if (y > 0 && y < i - 1 && x > 0 && x < ft_strlen(tab[y]) - 1)
		{
			tab[y][x] = '*';
			close_map(tab, x - 1, y, parser);
			close_map(tab, x + 1, y, parser);
			close_map(tab, x, y - 1, parser);
			close_map(tab, x, y + 1, parser);
		}
		else
			print_err("map ouverte", parser);
	}
	else if (tab[y][x] != '1' && tab[y][x] != '*')
		print_err("Caractere incorrect dans la map", parser);
	return (1);
}

int	parse_map(t_parser *parser)
{
	char	**tab;

	tab = parser->map;
	if (!find_user(tab, parser))
		return (0);
	if (parser->spawnx == -1)
		print_err("position du joueur inexistante", parser);
	close_map(tab, parser->spawnx, parser->spawny, parser);
	return (1);
}

int	find_map(t_parser *parser)
{
	int		i;
	int		y;
	char	**tab;

	i = -1;
	y = 0;
	tab = ft_split(parser->full_file, '\n');
	while (tab[++i])
	{
		while (ft_strchr(" \t10", tab[i][y]))
		{
			if (!tab[i][y])
			{
				ft_free_split(tab);
				return (i);
			}
			y++;
		}
		y = 0;
	}
	ft_free_split(tab);
	print_err("Map incorrect ou inexistante", parser);
	return (0);
}

int	analyse_map(t_parser *parser)
{
	int	i;
	int	n;
	int	nb_ligne;

	i = -1;
	n = 0;
	if (parser->ind != 420)
		print_err("Informations Manquantes", parser);
	nb_ligne = find_map(parser);
	while (parser->full_file[++i] && n < nb_ligne)
		if (parser->full_file[i] == '\n' && parser->full_file[i + 1] != '\n')
			n++;
	parser->map = ft_split(parser->full_file + i, 10);
	if (!parser->map)
		return (0);
	while (parser->full_file[++i])
		if (parser->full_file[i] == '\n' && parser->full_file[i + 1] == '\n')
			print_err("Ligne vide dans la map", parser);
	parse_map(parser);
	return (1);
}
