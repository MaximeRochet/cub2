#include "../includes/cub3d.h"

void print_struct(t_parse stock)

{
	printf("adr stock = %p\n", &stock);
	printf("\n");
	printf("|_________________________|\n");
	printf("|       __STOCK__         |\n");
	printf("| error = %d\n", stock.error);
	printf("| file  = \n%s \n", stock.file);
	printf("| map_file  = \n%s \n", stock.file_map);
	printf("| ind = %d \n", stock.ind);
	printf("| \n");

	printf("|        __RES__          |\n");
	printf("| x  = %d \n", stock.res.x);
	printf("| y  = %d \n", stock.res.y);
	printf("| \n");

	printf("|        __F__            |\n");
	printf("| r  = %d \n", stock.f.r);
	printf("| g  = %d \n", stock.f.g);
	printf("| b  = %d \n", stock.f.b);
	printf("| \n");

	printf("|         __C__           |\n");
	printf("| r  = %d \n", stock.c.r);
	printf("| g  = %d \n", stock.c.g);
	printf("| b  = %d \n", stock.c.b);
	printf("| \n");

	printf("|        __PATH__         |\n");
	printf("| NO = %s \n", stock.path.NO);
	printf("| SO = %s \n", stock.path.SO);
	printf("| WE = %s \n", stock.path.WE);
	printf("| EA = %s \n", stock.path.EA);
	printf("| S = %s \n", stock.path.S);
	printf("| \n");

	printf("|        __MAP__          |\n");
	printf("| user_x  = %d \n", stock.map.user_x);
	printf("| user_y  = %d \n", stock.map.user_y);
	printf("| user_deg = %d \n", stock.map.user_deg);	
	printf("|_________________________|\n");
}

