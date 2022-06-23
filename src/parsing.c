/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:44:47 by mrochet           #+#    #+#             */
/*   Updated: 2022/05/31 13:54:01 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	recreate_map(t_parser *parser)
{
	int	i;
	int	y;

	i = -1;
	while (parser->map[++i])
	{
		y = -1;
		while (parser->map[i][++y])
		{
			if (parser->map[i][y] == '*')
				parser->map[i][y] = '0';
		}
		if (parser->linelength < y)
		{
			parser->linelength = y;
		}
	}
	parser->linenb = i;
}

char	*ft_strjoin_cub(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		y;

	i = 0;
	y = 0;
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (0);
	if (s1)
	{
		while (s1[i])
		{
			ret[i] = s1[i];
			i++;
		}
	}
	while (s2[y])
		ret[i++] = s2[y++];
	ret[i] = '\0';
	free(s1);
	return (ret);
}

char	*read_file(char *fichier, t_parser *parser)
{
	int		fd;
	char	buffer[10];
	char	*fc;
	int		read_value;
	char	*tmp;

	fc = malloc(1);
	fc[0] = '\0';
	fd = open(fichier, O_RDONLY);
	if (fd == -1 || !fc)
		return (0);
	read_value = 1;
	while (read_value)
	{
		read_value = read(fd, buffer, 9);
		buffer[read_value] = '\0';
		fc = ft_strjoin_cub(fc, buffer);
	}
	close (fd);
	return (fc);
}

void	verif_name(char *namefile, t_parser *parser)
{
	int	size;

	size = ft_strlen(namefile);
	if (ft_strncmp((namefile + (size - 4)), ".cub", 5))
		print_err("Nom du fichier invalide", parser);
}

int	parsing(char *name_file, t_parser *parser)
{
	verif_name(name_file, parser);
	parser->full_file = read_file(name_file, parser);
	if (!parser->full_file)
		print_err("Fichier Illisible", parser);
	analyse_file(parser);
	analyse_map(parser);
	recreate_map(parser);
	return (1);
}
