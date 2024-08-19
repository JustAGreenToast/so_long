/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 12:58:03 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/19 13:13:07 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

unsigned int	*get_pixel_ptr(t_img *img, t_point pos)
{
	char	*dst;

	dst = img->addr + (pos.y * img->cols + pos.x * (img->bpp / 8));
	return ((unsigned int *)dst);
}

void	draw_pixel(t_img *img, t_point pos, unsigned int color)
{
	unsigned int	*dst;

	if ((color & 0xFF000000) > (*get_pixel_ptr(img, pos) & 0xFF000000))
		return ;
	dst = get_pixel_ptr(img, pos);
	*dst = color;
}

void	draw_sprite(t_sprite *spr, t_img *img, t_point pos)
{
	int				x;
	int				y;
	unsigned int	color;

	if (spr == NULL)
		return ;
	y = 0;
	while (y < spr->height)
	{
		x = 0;
		while (x < spr->width)
		{
			color = *get_pixel_ptr(&spr->img_data, get_point(x, y));
			draw_pixel(img, get_point(pos.x + x, pos.y + y), color);
			x++;
		}
		y++;
	}
}
