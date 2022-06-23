/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:04:02 by mrochet           #+#    #+#             */
/*   Updated: 2022/05/31 13:54:50 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	verif_fc(char *str, t_parser *parser)
{
	char	**tab;
	int		i;
	int		y;

	i = -1;
	y = -1;
	if (str[0] == 'F' && parser->f != -1)
		print_err("Ligne F multiple", parser);
	if (str[0] == 'C' && parser->c != -1)
		print_err("Ligne C multiple", parser);
	while (!ft_isdigit(*str))
		str++;
	tab = ft_split(str, ',');
	while (tab[++i])
	{
		while (tab[i][++y])
			if (!ft_isdigit(tab[i][y]))
				print_err("Element non digit dans F ou C", parser);
		y = -1;
		if (!(atoi(tab[i]) <= 255 && atoi(tab[i]) >= 0) || i == 3)
			print_err("Couleur = 3 chiffre entre 0 et 255", parser);
	}
	ft_free_split(tab);
	return (1);
}

void	parse_fc(char *file_fc, t_parser *parser)
{
	char	**tab;
	char	c;

	if (!(verif_fc(file_fc, parser)))
		return ;
	c = file_fc[0];
	while (!ft_isdigit(*file_fc))
		file_fc++;
	tab = ft_split(file_fc, ',');
	if (!tab[1] || !tab[2])
		print_err("F et C doivent contenir 3 couleurs", parser);
	if (c == 'F')
		parser->f = color(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]));
	if (c == 'C')
		parser->c = color(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]));
	parser->ind += 10;
	ft_free_split(tab);
}
