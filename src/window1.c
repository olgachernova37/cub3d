/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:02:00 by olcherno          #+#    #+#             */
/*   Updated: 2026/03/11 14:07:00 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	fill_rect(t_app *app, int x0, int y0, int size, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			put_pixel(app, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

static int	min_int(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static int	map_tile_size(t_app *app)
{
	int	tile_w;
	int	tile_h;
	int	tile;

	if (!app->map.width || !app->map.height)
		return (1);
	tile_w = app->width / app->map.width;
	tile_h = app->height / app->map.height;
	tile = min_int(tile_w, tile_h);
	if (tile < 1)
		tile = 1;
	if (tile > 32)
		tile = 32;
	return (tile);
}

void    initialize_image(t_app *app)
{
	app->img = mlx_new_image(app->mlx, app->width, app->height);
	if (!app->img)
	{
		ft_putstr_fd("Error: mlx_new_image failed\n", 2);
		close_app(app);
	}
	app->addr = mlx_get_data_addr(app->img, &app->bpp, &app->line_len, &app->endian);
	if (!app->addr)
	{
		ft_putstr_fd("Error: mlx_get_data_addr failed\n", 2);
		close_app(app);
	}
}

static void	draw_map(t_app *app)
{
	int	tile;
	int	x;
	int	y;
	char	cell;

	tile = map_tile_size(app);
	y = 0;
	while (y < app->map.height)
	{
		x = 0;
		while (x < app->map.width)
		{
			if (x < (int)ft_strlen(app->map.grid[y]))
				cell = app->map.grid[y][x];
			else
				cell = ' ';
			if (cell == '1')
				fill_rect(app, x * tile, y * tile, tile, 0xB0B0B0);
			else
				fill_rect(app, x * tile, y * tile, tile, 0x202020);
			if (x == app->map.player_x && y == app->map.player_y)
				fill_rect(app, x * tile + tile / 4, y * tile + tile / 4,
					tile / 2, 0xFF0000);
			x++;
		}
		y++;
	}
}

int    render(t_app *app)
{
	int	x;
	int	y;

	y = 0;
	while (y < app->height)
	{
		x = 0;
		while (x < app->width)
		{
			put_pixel(app, x, y, app->config.ceiling_color);
			x++;
		}
		y++;
	}
	y = app->height / 2;
	while (y < app->height)
	{
		x = 0;
		while (x < app->width)
		{
			put_pixel(app, x, y, app->config.floor_color);
			x++;
		}
		y++;
	}
	draw_map(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
	return (0);
}

void	put_pixel(t_app *app, int x, int y, int color)
{
	int	offset;

	if (x < 0 || y < 0 || x >= app->width || y >= app->height)
		return ;
	offset = y * app->line_len + x * (app->bpp / 8);
	*(int *)(app->addr + offset) = color;
}
