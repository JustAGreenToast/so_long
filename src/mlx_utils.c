/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:54:58 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/19 17:21:56 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	exit_game(int keycode)
{
	(void)keycode;
	game_exit(EXIT_QUIT);
	return (0);
}

static int	key_pressed(int keycode, t_data *data)
{
	if (keycode == 53 || keycode == 12)
		exit_game(keycode);
	else if (move_player(keycode, data))
		draw_scene(data);
	return (0);
}

void	create_win(t_data *data)
{
	data->mlx_data.win = mlx_new_window(data->mlx_data.mlx,
			data->mlx_data.size.x, data->mlx_data.size.y, "so_long");
	if (!data->mlx_data.win)
		error_exit(ERR_WIN);
	create_img(&data->mlx_data.win_img, data->mlx_data.mlx,
		data->mlx_data.size.x, data->mlx_data.size.y);
	mlx_hook(data->mlx_data.win, 2, 0, key_pressed, data);
	mlx_hook(data->mlx_data.win, 17, 0, exit_game, NULL);
}

void	create_img(t_img *img_data, void *mlx, int width, int height)
{
	int	bpp;
	int	cols;
	int	endian;

	img_data->img = mlx_new_image(mlx, width, height);
	if (!img_data->img)
		error_exit(ERR_IMG);
	img_data->addr = mlx_get_data_addr(img_data->img, &bpp, &cols, &endian);
	if (!img_data->addr)
		error_exit(ERR_IMG);
	img_data->bpp = bpp;
	img_data->cols = cols;
	img_data->endian = endian;
}
