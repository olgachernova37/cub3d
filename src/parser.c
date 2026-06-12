#include "../cub3d.h"

static void	free_strtab_local(char **tab)
{
	int	index;

	if (!tab)
		return ;
	index = 0;
	while (tab[index])
	{
		free(tab[index]);
		index++;
	}
	free(tab);
}

void	free_strtab(char **tab)
{
	free_strtab_local(tab);
}

static char	*dup_line(const char *line)
{
	char	*copy;
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	copy[len] = '\0';
	while (len > 0)
	{
		len--;
		copy[len] = line[len];
	}
	return (copy);
}

static int	is_blank_line(const char *line)
{
	int	index;

	index = 0;
	while (line[index] == ' ' || line[index] == '\t' || line[index] == '\n'
		|| line[index] == '\r')
		index++;
	return (line[index] == '\0');
}

static int	starts_map(const char *line)
{
	int	index;

	index = 0;
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	return (line[index] == '1' || line[index] == '0'
		|| line[index] == 'N' || line[index] == 'S'
		|| line[index] == 'E' || line[index] == 'W');
}

static void	append_grid_line(t_app *app, char *line)
{
	char	**grid;
	int		index;

	grid = malloc(sizeof(char *) * (app->map.height + 2));
	if (!grid)
		return ;
	index = 0;
	while (index < app->map.height)
	{
		grid[index] = app->map.grid[index];
		index++;
	}
	grid[index] = line;
	grid[index + 1] = NULL;
	free(app->map.grid);
	app->map.grid = grid;
	app->map.height++;
	if ((int)ft_strlen(line) > app->map.width)
		app->map.width = ft_strlen(line);
}

static int	set_color(int *dst, const char *line)
{
	int	index;
	int	red;
	int	green;
	int	blue;

	index = 1;
	while (line[index] == ' ' || line[index] == '\t')
		index++;
	red = ft_atoi(line + index);
	while (line[index] && line[index] != ',')
		index++;
	if (line[index] != ',')
		return (1);
	green = ft_atoi(line + ++index);
	while (line[index] && line[index] != ',')
		index++;
	if (line[index] != ',')
		return (1);
	blue = ft_atoi(line + ++index);
	if (red < 0 || red > 255 || green < 0 || green > 255
		|| blue < 0 || blue > 255)
		return (1);
	*dst = (red << 16) | (green << 8) | blue;
	return (0);
}

static int	parse_header_line(t_app *app, char *line)
{
	char	**parts;

	if (line[0] == 'R' && line[1] == ' ')
	{
		parts = ft_split(line + 1, ' ');
		if (!parts || !parts[0] || !parts[1])
		{
			free_strtab(parts);
			return (1);
		}
		app->width = ft_atoi(parts[0]);
		app->height = ft_atoi(parts[1]);
		free_strtab(parts);
		return (0);
	}
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (free(app->config.no_texture), app->config.no_texture = dup_line(line + 3), 0);
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (free(app->config.so_texture), app->config.so_texture = dup_line(line + 3), 0);
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (free(app->config.we_texture), app->config.we_texture = dup_line(line + 3), 0);
	if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (free(app->config.ea_texture), app->config.ea_texture = dup_line(line + 3), 0);
	if (line[0] == 'F' && line[1] == ' ')
		return (set_color(&app->config.floor_color, line), 0);
	if (line[0] == 'C' && line[1] == ' ')
		return (set_color(&app->config.ceiling_color, line), 0);
	return (0);
}

static int	validate_map(t_app *app)
{
	int	y;
	int	x;
	int	players;
	char	cell;

	players = 0;
	y = 0;
	while (y < app->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(app->map.grid[y]))
		{
			cell = app->map.grid[y][x];
			if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
			{
				app->map.player_x = x;
				app->map.player_y = y;
				app->map.player_dir = cell;
				players++;
				app->map.grid[y][x] = '0';
			}
			else if (cell != '0' && cell != '1' && cell != ' ')
				return (1);
			x++;
		}
		y++;
	}
	return (players != 1);
}

int	parse_cub(const char *path, t_app *app)
{
	int	fd;
	char	*line;
	int	map_started;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	map_started = 0;
	app->config.floor_color = 0x202020;
	app->config.ceiling_color = 0x808080;
	app->map.grid = NULL;
	app->map.width = 0;
	app->map.height = 0;
	app->map.player_x = -1;
	app->map.player_y = -1;
	app->map.player_dir = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_blank_line(line))
		{
			free(line);
			if (map_started)
			{
				close(fd);
				return (1);
			}
			continue ;
		}
		if (!map_started && starts_map(line))
			map_started = 1;
		if (map_started)
			append_grid_line(app, dup_line(line));
		else
			parse_header_line(app, line);
		free(line);
	}
	close(fd);
	if (!app->map.grid || validate_map(app))
		return (1);
	return (0);
}