/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:24:25 by olcherno          #+#    #+#             */
/*   Updated: 2025/06/18 14:49:54 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"



int	main(int argc, char **argv)
{
	t_map	game;

	game.map = NULL;
	game.coin = 0;
	game.map_e = 0;
	game.map_p = 0;
	game.point = 50;
	
	game.map = read_map(argv[1]);
	if (!game.map)
	{
		ft_printf("Error → Failed to read map.\n");
		exit(1);
	}
	print_map(game.map);
	check_map(&game);
	ft_init_window(&game);
	if (game.map)
		free_map(game.map);
	return (0);
}
