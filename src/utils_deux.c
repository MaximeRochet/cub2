/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_deux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:55:07 by mrochet           #+#    #+#             */
/*   Updated: 2022/05/31 14:55:25 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_strs(char **tab, int len)
{
	int	i;

	i = 0;
	if (len != -1)
	{
		while (i < len)
		{
			free(tab[i]);
			i++;
		}
	}
	else
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}

void	ft_free_split(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	color(int r, int g, int b)
{
	int	base;

	base = 256;
	return (r * base * base + g * base + b);
}

void	free_parser(t_parser *parser)
{
	int	i;

	i = 0;
	if (parser->full_file)
		free(parser->full_file);
	while (i < 4)
	{
		if (parser->text[i])
			free(parser->text[i]);
		i++;
	}
	if (parser->map)
		free_strs(parser->map, -1);
}
