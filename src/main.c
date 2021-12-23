/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 18:23:36 by mrochet           #+#    #+#             */
/*   Updated: 2021/12/23 16:40:50 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int ac, char **av)
{
	(void)ac;
	int i = 0;
	t_parse *stock;
	
	if(ac != 2)
		return(print_err("mauvais nombre d'argument", stock));
	stock = calloc(1,sizeof(t_parse));
	if (!stock)
		return(0);
	init_t_parse(stock);	
	printf("parsing = %d\n", parsing(av[1], stock));
	//print_struct(*stock);

	return(0);

}
