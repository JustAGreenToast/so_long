/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:57:36 by pfontenl          #+#    #+#             */
/*   Updated: 2024/01/19 17:19:49 by pfontenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(enum e_errors err)
{
	ft_printf_err("Error\n");
	if (err == ERR_ARGS)
		ft_printf_err("Incorrect amount of arguments (1 expected).\n");
	else if (err == ERR_FILE)
		ft_printf_err("Invalid file extension: only '.ber' files are valid.\n");
	else if (err == ERR_READ)
		ft_printf_err("Could not read file.\n");
	else if (err == ERR_MALLOC)
		ft_printf_err("Memory allocation failed.\n");
	else if (err == ERR_MAP)
		ft_printf_err("Invalid map.\n");
	else if (err == ERR_IMG)
		ft_printf_err("Could not generate image.\n");
	else if (err == ERR_MLX)
		ft_printf_err("MiniLibX loop was unexpectedly stopped.\n");
	else
	{
		ft_printf_err("An undefined error has occurred. Sorry :(\n");
		ft_printf_err("Error code: %d\n", (int)err);
	}
	exit(1);
}

void	game_exit(enum e_exits exit_code)
{
	if (exit_code == EXIT_GOAL)
		ft_printf("BRO YOU ARE WINRAR !! !1! :D\n");
	else if (exit_code == EXIT_QUIT)
		ft_printf("Game closed successfully.\n");
	else
		ft_printf("Game closed successfully with exit code %d.",
			(int)exit_code);
	exit(0);
}
