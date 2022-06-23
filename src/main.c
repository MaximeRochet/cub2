/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:07:10 by mrochet           #+#    #+#             */
/*   Updated: 2022/05/31 15:09:06 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	print_err(char *mssg_err, t_parser *parser)
{
	free_parser(parser);
	printf("Erreur\n%s\n", mssg_err);
	exit(0);
}

static t_parser	*init_parser(void)
{
	t_parser	*ret;

	ret = malloc(sizeof(t_parser));
	if (!ret)
		return (0);
	ft_bzero(ret, sizeof(t_parser));
	ret->f = -1;
	ret->c = -1;
	ret->spawnx = -1;
	ret->spawny = -1;
	ret->spawndir = 0;
	ret->ind = 0;
	ret->map = NULL;
	return (ret);
}

int	main(int ac, char **av)
{
	t_parser	*parser;

	parser = init_parser();
	if (ac != 2)
		print_err("Mauvais Nombre D'Argument", parser);
	if (!parser)
		print_err("Error Malloc Parser", parser);
	if (parsing(av[1], parser))
	{
		print_struct(parser);
		run(parser);
	}
	return (0);
}
