/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:52:05 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/19 17:26:35 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void		clear_img(t_img *img, unsigned int color, t_point size);
static t_sprite	*get_tile_sprite(char tile, t_data *data);
static void		draw_map(t_data *data);
static void		draw_player(t_data *data);

void	draw_scene(t_data *data)
{
	clear_img(&data->mlx_data.win_img, 0, data->mlx_data.size);
	draw_map(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx_data.mlx, data->mlx_data.win,
		data->mlx_data.win_img.img, 0, 0);
}

static void	clear_img(t_img *img, unsigned int color, t_point size)
{
	t_point	pos;

	pos.y = 0;
	while (pos.y < size.y)
	{
		pos.x = 0;
		while (pos.x < size.x)
		{
			draw_pixel(img, pos, color);
			pos.x++;
		}
		pos.y++;
	}
}

static t_sprite	*get_tile_sprite(char tile, t_data *data)
{
	if (tile == TILE_WALL)
		return (&data->sprites[0]);
	if (tile == TILE_COIN)
		return (&data->sprites[1]);
	if (tile == TILE_GOAL)
		return (&data->sprites[2]);
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
		draw_sprite(get_tile_sprite(data->map_data.map[i], data),
			&data->mlx_data.win_img, get_point(x_pos * 16, y_pos * 16));
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

static void	draw_player(t_data *data)
{
	t_point	pos;

	pos = get_point(data->player_data.pos % (data->map_data.cols + 1),
			data->player_data.pos / (data->map_data.cols + 1));
	pos = scale_point(pos, 16);
	draw_sprite(&data->sprites[3], &data->mlx_data.win_img, pos);
}
