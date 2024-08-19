/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 12:48:39 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/19 17:32:30 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	load_sprites(t_data *data);

void	init_mlx(t_data *data)
{
	data->mlx_data.mlx = mlx_init();
	if (!data->mlx_data.mlx)
		error_exit(ERR_MALLOC);
	data->mlx_data.size = get_point(16 * data->map_data.cols, 16
			* data->map_data.rows);
	data->mlx_data.scale = 1;
	data->mlx_data.win = NULL;
	data->mlx_data.win_img.img = NULL;
	create_win(data);
	load_sprites(data);
	draw_scene(data);
}

static void	load_sprites(t_data *data)
{
	load_xpm_sprite("img/Wall.xpm", data->mlx_data.mlx, &data->sprites[0]);
	load_xpm_sprite("img/Coin.xpm", data->mlx_data.mlx, &data->sprites[1]);
	load_xpm_sprite("img/Goal.xpm", data->mlx_data.mlx, &data->sprites[2]);
	load_xpm_sprite("img/Spikes.xpm", data->mlx_data.mlx, &data->sprites[3]);
	load_xpm_sprite("img/Mimic.xpm", data->mlx_data.mlx, &data->sprites[4]);
	load_xpm_sprite("img/Player/Up.xpm", data->mlx_data.mlx, &data->sprites[5]);
	load_xpm_sprite("img/Player/Right.xpm", data->mlx_data.mlx,
		&data->sprites[6]);
	load_xpm_sprite("img/Player/Down.xpm", data->mlx_data.mlx,
		&data->sprites[7]);
	load_xpm_sprite("img/Player/Left.xpm", data->mlx_data.mlx,
		&data->sprites[8]);
	load_xpm_sprite("img/Player/Neutral.xpm", data->mlx_data.mlx,
		&data->sprites[9]);
}

void	load_xpm_sprite(char *path, void *mlx, t_sprite *sprite)
{
	void	*img;
	int		data[5];

	img = mlx_xpm_file_to_image(mlx, path, &data[0], &data[1]);
	if (!img)
		error_exit(ERR_IMG);
	sprite->img_data.img = img;
	sprite->width = data[0];
	sprite->height = data[1];
	sprite->img_data.addr = mlx_get_data_addr(sprite->img_data.img, &data[2],
			&data[3], &data[4]);
	if (!sprite->img_data.addr)
		error_exit(ERR_IMG);
	sprite->img_data.bpp = data[2];
	sprite->img_data.cols = data[3];
	sprite->img_data.endian = data[4];
}
