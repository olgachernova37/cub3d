/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 00:00:00 by olcherno          #+#    #+#             */
/*   Updated: 2026/03/11 00:00:00 by olcherno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs/libft/libft.h"
# include "libs/minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>

# define WIN_W		1280
# define WIN_H		720
# define WIN_TITLE	"cub3D"

# define KEY_ESC	65307

typedef struct s_app
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;

	void    *img;       // the image object
	char    *addr;      // raw pixel memory
	int     bpp;        // bits per pixel for mlx_get_data_addr
	int     line_len;   // bytes per row for mlx_get_data_addr
	int     endian;

}	t_app;

/* window.c */
void	init_app(t_app *app);
int		close_app(t_app *app);
int		key_handler(int keycode, t_app *app);

/* window1.c */
void    initialize_image(t_app *app);

#endif
