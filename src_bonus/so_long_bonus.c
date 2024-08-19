/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:38:38 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/19 17:57:41 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	check_extension(char *path);

int	main(int argn, char **args)
{
	t_data	data;

	if (argn != 2)
		error_exit(ERR_ARGS);
	check_extension(args[1]);
	create_map(read_map(args[1]), &data.map_data);
	data.player_data.pos = data.map_data.spawn;
	data.player_data.dir = 1;
	data.player_data.move_count = 0;
	init_mlx(&data);
	mlx_loop(data.mlx_data.mlx);
	error_exit(ERR_MLX);
	return (1);
}

static void	check_extension(char *path)
{
	size_t	i;

	i = 0;
	while (path[i])
		i++;
	if (i <= 4)
		error_exit(ERR_FILE);
	i -= 4;
	if (path[i++] != '.' || path[i++] != 'b' || path[i++] != 'e'
		|| path[i++] != 'r')
		error_exit(ERR_FILE);
}
