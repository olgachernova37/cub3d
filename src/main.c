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

int	main(void)
{
	t_app	app;

	init_app(&app);
	/* Event 17 = ClientMessage (window manager "close" / X button) */
	mlx_hook(app.win, 17, 0, close_app, &app);
	/* Event 2 = KeyPress */
	mlx_hook(app.win, 2, 1L << 0, key_handler, &app);
	mlx_loop_hook(app.mlx, render, &app);
	mlx_loop(app.mlx);
	return (0);
}
