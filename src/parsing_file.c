/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:57:18 by mrochet           #+#    #+#             */
/*   Updated: 2022/05/31 13:55:30 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*verif_path(char *str, t_parser *parser)
{
	char	*charset;
	int		fd;

	charset = "NSOWEA ";
	while (ft_strchr(charset, *str))
		str++;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		print_err("Chemin de texture incorrect", parser);
	close(fd);
	return (str);
}

void	parse_path(char *file_path, t_parser *parser)
{
	char	*path;

	path = verif_path(file_path, parser);
	if (!path)
		return ;
	if (file_path[0] == 'N' && file_path[1] == 'O' \
			&& parser->text[NORTH] == NULL)
		parser->text[NORTH] = ft_strdup(path);
	if (file_path[0] == 'S' && file_path[1] == 'O' \
			&& parser->text[SOUTH] == NULL)
		parser->text[SOUTH] = ft_strdup(path);
	if (file_path[0] == 'E' && file_path[1] == 'A' \
			&& parser->text[EAST] == NULL)
		parser->text[EAST] = ft_strdup(path);
	if (file_path[0] == 'W' && file_path[1] == 'E' \
			&& parser->text[WEST] == NULL)
		parser->text[WEST] = ft_strdup(path);
	parser->ind += 100;
}

void	redirect(char *file, t_parser *parser)
{
	char	*charset;

	charset = "SNWE";
	if (ft_strchr(charset, file[0]))
		parse_path(file, parser);
	else if (file[0] == 'F')
		parse_fc(file, parser);
	else if (file[0] == 'C')
		parse_fc(file, parser);
}

void	analyse_file(t_parser *parser)
{
	char	**tab;
	int		i;
	int		y;

	i = -1;
	y = 0;
	tab = ft_split(parser->full_file, 10);
	while (tab[++i])
	{
		y = 0;
		while (tab[i][y] <= 32)
			y++;
		if (strchr("NSWESFC", tab[i][y]))
			redirect(tab[i] + y, parser);
		else if (!strchr("1 02NEWS\n", tab[i][y]))
			print_err("Ligne incorrect dans le .cub", parser);
	}
	ft_free_split(tab);
	if (!parser->text[NORTH] || !parser->text[SOUTH] \
			|| !parser->text[EAST] || !parser->text[WEST])
		print_err("Information Manquantes", parser);
}
