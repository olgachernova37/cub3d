/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2026/03/11 00:00:00 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_args(int ac, char **av)
{
	size_t	len;

	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	len = ft_strlen(av[1]);
	if (len < 5 || ft_strncmp(av[1] + len - 4, ".cub", 4) != 0)
	{
		ft_putstr_fd("Error: map file must have .cub extension\n", 2);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_app	app;

	if (check_args(ac, av))
		return (1);
	ft_bzero(&app, sizeof(app));
	init_app(&app);
	/* Event 17 = ClientMessage (window manager "close" / X button) */
	mlx_hook(app.win, 17, 0, close_app, &app);
	/* Event 2 = KeyPress */
	mlx_hook(app.win, 2, 1L << 0, key_handler, &app);
	mlx_loop_hook(app.mlx, render, &app);
	mlx_loop(app.mlx);
	return (0);
}
