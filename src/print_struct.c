/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:36:27 by mrochet           #+#    #+#             */
/*   Updated: 2022/05/31 13:43:36 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_struct_deux(t_parser *parser)
{
	int	i;

	i = 0;
	printf("|        __MAP__          |\n");
	printf("| user_x  = %d \n", parser->spawnx);
	printf("| user_y  = %d \n", parser->spawny);
	printf("| user_deg = %d \n", parser->spawndir);
	printf("| linelength = %d \n", parser->linelength);
	printf("| line nb = %d \n", parser->linenb);
	printf("\n| file map  = \n");
	while (parser->map[i])
		printf("%s\n", parser->map[i++]);
	printf("\n|_________________________|\n");
}

void	print_struct(t_parser *parser)

{
	int	i;

	i = 0;
	printf("adr parser= %p\n", &parser);
	printf("\n");
	printf("|_________________________|\n");
	printf("|       __parser_         |\n");
	printf("| ind = %d \n", parser->ind);
	printf("| \n");
	printf("| file complet =\n%s\n", parser->full_file);
	printf("|         __F__           |\n");
	printf("| b  = %d \n", parser->f);
	printf("| \n");
	printf("|         __C__           |\n");
	printf("| r  = %d \n", parser->c);
	printf("| \n");
	printf("|        __PATH__         |\n");
	while (i < 4)
		printf("%s\n", parser->text[i++]);
	printf("| \n");
	print_struct_deux(parser);
}
