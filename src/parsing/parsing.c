/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:04:04 by mrochet           #+#    #+#             */
/*   Updated: 2021/12/23 16:41:59 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*read_file(char *fichier)
{
	int		fd;
	char	buffer[100];
	char	*fc;
	int		read_value;
	char	*tmp;

	fc = NULL;
	fd = open(fichier, O_RDONLY);
	prinft("%s  %d\n", fichier, fd);
	if (fd == -1)
		return (0);
	read_value = 1;
	while (read_value)
	{
		read_value = read(fd, buffer, 99);
		buffer[read_value] = '\0';
		tmp = ft_strjoin(fc, buffer);
		free(fc);
		fc = tmp;
	}
	close (fd);
	return (fc);
}

int	verif_name(char *namefile, t_parse *stock)
{
	int	size;

	size = ft_strlen(namefile);
	if (ft_strncmp((namefile + (size - 4)), ".cub", 5))
		return (print_err("Nom du fichier invalide", stock));
	return (1);
}

int	print_f_err(char *mssg_err, void *test, t_parse *stock)
{
	if (test)
		free(test);
	stock->error = 1;
	printf("Erreur\n%s\n", mssg_err);
	return (0);
}

int	print_err(char *mssg_err, t_parse *stock)
{
	stock->error = 1;
	printf("Erreur\n%s\n", mssg_err);
	return (0);
}

int	parsing(char *name_file, t_parse *stock)
{
	char	*file;

	if (!name_file)
		return (print_err("mauvais nombre d'argument", stock));
	verif_name(name_file, stock);
	file = read_file(name_file);
	if (!file)
		return (print_err("fichier illisibles", stock));
	stock->file = file;
	analyse_file(file, stock);
	if (stock->error)
		return (0);
	return (1);
}
