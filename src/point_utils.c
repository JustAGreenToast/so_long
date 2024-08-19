/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:46:43 by pfontenl          #+#    #+#             */
/*   Updated: 2023/12/11 18:58:40 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_point	get_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_point	add_points(t_point a, t_point b)
{
	return (get_point(a.x + b.x, a.y + b.y));
}

t_point	scale_point(t_point p, int s)
{
	return (get_point(p.x * s, p.y * s));
}
