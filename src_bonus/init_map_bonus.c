/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:43:40 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/21 13:42:09 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	rect_check(char *data, t_map *map);
static int	flood_check(char *map, size_t start);
static void	recursive_flood(char *map, size_t i, int *new_tile,
				int *found_goal);
static int	check_grid(char *map, int *unchecked_tiles);

void	create_map(char *data, t_map *map)
{
	int	spawn;
	int	goal;
	int	coins;

	spawn = ft_find_char(data, TILE_SPAWN);
	goal = ft_find_char(data, TILE_GOAL);
	coins = ft_count_char(data, TILE_COIN);
	if (coins <= 0 || ft_count_char(data, TILE_SPAWN) != 1
		|| ft_count_char(data, TILE_GOAL) != 1)
		error_exit(ERR_MAP);
	if (!rect_check(data, map) || !flood_check(data, spawn))
		error_exit(ERR_MAP);
	map->map = data;
	map->revealed = ft_calloc(ft_strlen(data), sizeof(char));
	if (!map->revealed)
		error_exit(ERR_MALLOC);
	map->spawn = (size_t)spawn;
	map->goal = (size_t)goal;
	map->coins = (size_t)coins;
}

static int	rect_check(char *data, t_map *map)
{
	size_t	cols;

	if (!data)
		return (0);
	cols = ft_line_len(data);
	map->cols = cols;
	data += cols;
	if (*data == '\n')
		data++;
	map->rows = 1;
	while (*data)
	{
		if (ft_line_len(data) != cols)
			return (0);
		map->rows++;
		data += ft_line_len(data);
		if (*data == '\n')
			data++;
	}
	return (1);
}

static int	flood_check(char *map, size_t start)
{
	size_t	i;
	int		out;
	int		*new_tile;

	new_tile = malloc(ft_strlen(map) * sizeof(int));
	if (!new_tile)
		error_exit(ERR_MALLOC);
	i = 0;
	while (i < ft_strlen(map))
	{
		new_tile[i] = 1;
		i++;
	}
	out = 0;
	recursive_flood(map, start, new_tile, &out);
	if (!check_grid(map, new_tile))
		error_exit(ERR_MAP);
	free(new_tile);
	return (out);
}

static void	recursive_flood(char *map, size_t i, int *new_tile, int *found_goal)
{
	size_t	cols;

	if (i >= ft_strlen(map))
		error_exit(ERR_MAP);
	cols = ft_line_len(map) + 1;
	if (!new_tile[i] || map[i] == TILE_WALL || map[i] == TILE_SPIKE
		|| map[i] == TILE_MIMIC)
		return ;
	if (i < cols || i % cols == 0 || i % cols == cols - 1)
		error_exit(ERR_MAP);
	if (map[i] == TILE_GOAL)
		*found_goal = 1;
	new_tile[i] = 0;
	recursive_flood(map, i - 1, new_tile, found_goal);
	recursive_flood(map, i + 1, new_tile, found_goal);
	recursive_flood(map, i - cols, new_tile, found_goal);
	recursive_flood(map, i + cols, new_tile, found_goal);
}

static int	check_grid(char *map, int *unchecked_tiles)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		if (map[i] != '\n' && map[i] != TILE_EMPTY && map[i] != TILE_WALL
			&& map[i] != TILE_COIN && map[i] != TILE_GOAL
			&& map[i] != TILE_SPAWN && map[i] != TILE_SPIKE
			&& map[i] != TILE_MIMIC)
			return (0);
		if (map[i] == TILE_COIN && unchecked_tiles[i])
			return (0);
		i++;
	}
	return (1);
}
