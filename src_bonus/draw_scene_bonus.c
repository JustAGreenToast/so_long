/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:52:05 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/19 17:30:46 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void		clear_img(t_img *img, unsigned int color, t_point size,
					int scale);
static t_sprite	*get_tile_sprite(char tile, int map_pos, t_data *data);
static void		draw_map(t_data *data);
static void		draw_text(t_data *data);

void	draw_scene(t_data *data)
{
	unsigned int	bg_colors[4];
	int				bg_index;
	t_point			player_pos;
	t_sprite		*player_sprite;

	bg_colors[0] = 0x00101010;
	bg_colors[1] = 0x002F1F10;
	bg_colors[2] = 0x0010251F;
	bg_colors[3] = 0x001F1025;
	bg_index = data->player_data.move_count % 4;
	clear_img(&data->mlx_data.win_img, bg_colors[bg_index], data->mlx_data.size,
		data->mlx_data.scale);
	draw_map(data);
	player_pos = get_point(data->player_data.pos % (data->map_data.cols + 1),
			data->player_data.pos / (data->map_data.cols + 1));
	player_pos = scale_point(player_pos, 16);
	player_sprite = &data->sprites[data->player_data.dir + 5];
	if (data->player_data.move_count % 2)
		player_sprite = &data->sprites[9];
	draw_sprite(player_sprite, &data->mlx_data.win_img, player_pos,
		data->mlx_data.scale);
	mlx_put_image_to_window(data->mlx_data.mlx, data->mlx_data.win,
		data->mlx_data.win_img.img, 0, 0);
	draw_text(data);
}

static void	clear_img(t_img *img, unsigned int color, t_point size, int scale)
{
	t_point	pos;

	pos.y = 0;
	while (pos.y < size.y)
	{
		pos.x = 0;
		while (pos.x < size.x)
		{
			draw_pixel(img, pos, color, scale);
			pos.x++;
		}
		pos.y++;
	}
}

static t_sprite	*get_tile_sprite(char tile, int map_pos, t_data *data)
{
	if (tile == TILE_WALL)
		return (&data->sprites[0]);
	if (tile == TILE_COIN && data->map_data.revealed[map_pos])
		return (&data->sprites[1]);
	if (tile == TILE_GOAL)
		return (&data->sprites[2]);
	if (tile == TILE_SPIKE)
		return (&data->sprites[3]);
	if (tile == TILE_MIMIC)
		return (&data->sprites[4]);
	return (NULL);
}

static void	draw_map(t_data *data)
{
	size_t	i;
	size_t	x_pos;
	size_t	y_pos;

	i = 0;
	x_pos = 0;
	y_pos = 0;
	while (data->map_data.map[i])
	{
		draw_sprite(get_tile_sprite(data->map_data.map[i], i, data),
			&data->mlx_data.win_img, get_point(x_pos * 16, y_pos * 16),
			data->mlx_data.scale);
		i++;
		x_pos++;
		if (data->map_data.map[i] == '\n' || data->map_data.map[i] == '\r')
		{
			i++;
			x_pos = 0;
			y_pos++;
		}
	}
}

static void	draw_text(t_data *data)
{
	char	*text;

	text = ft_itoa(data->player_data.move_count);
	if (!text)
		error_exit(ERR_MALLOC);
	mlx_string_put(data->mlx_data.mlx, data->mlx_data.win, 0, 0, 0x0050FF50,
		text);
	free(text);
	text = ft_itoa(data->map_data.coins);
	if (!text)
		error_exit(ERR_MALLOC);
	mlx_string_put(data->mlx_data.mlx, data->mlx_data.win, 0, 12, 0x00FFFF50,
		text);
	free(text);
}
