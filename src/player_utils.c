/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:29:00 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/22 13:09:51 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_keycode_dir(int keycode);
static int	calc_move_offset(int dir, int cols);
static int	tile_stepped(char tile, int pos, t_data *data);

int	move_player(int keycode, t_data *data)
{
	int	new_pos;
	int	new_dir;

	new_dir = get_keycode_dir(keycode);
	if (new_dir < 0)
		return (0);
	new_pos = data->player_data.pos + calc_move_offset(new_dir,
			data->map_data.cols + 1);
	if (!tile_stepped(data->map_data.map[new_pos], new_pos, data))
		return (0);
	data->player_data.pos = new_pos;
	data->player_data.move_count++;
	ft_printf("Move count: %d\n", data->player_data.move_count);
	if (data->map_data.map[new_pos] == TILE_GOAL && !data->map_data.coins)
		game_exit(EXIT_GOAL);
	return (1);
}

static int	get_keycode_dir(int keycode)
{
	if (keycode == 126 || keycode == 13)
		return (0);
	if (keycode == 124 || keycode == 2)
		return (1);
	if (keycode == 125 || keycode == 1)
		return (2);
	if (keycode == 123 || keycode == 0)
		return (3);
	return (-1);
}

static int	calc_move_offset(int dir, int cols)
{
	if (dir == 0)
		return (-cols);
	if (dir == 1)
		return (1);
	if (dir == 2)
		return (cols);
	return (-1);
}

static int	tile_stepped(char tile, int pos, t_data *data)
{
	if (tile == TILE_WALL)
		return (0);
	if (tile == TILE_COIN)
	{
		data->map_data.map[pos] = TILE_EMPTY;
		data->map_data.coins--;
		ft_printf("Cherries left: %d\n", (int)data->map_data.coins);
	}
	if (tile == TILE_GOAL && data->map_data.coins)
		ft_printf("Cherries left: %d\n", (int)data->map_data.coins);
	return (1);
}
