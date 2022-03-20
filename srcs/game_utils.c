/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 12:39:44 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/20 16:15:01 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"

bool	is_power_of_two(int i)
{
	while (i != 1)
	{
		if (i % 2 != 0)
			return (false);
		i /= 2;
	}
	return (true);
}

void	set_color_pair(t_board *board, WINDOW *wnd, unsigned int color_pair)
{
	board->color_pair = color_pair;
	wattron(wnd, COLOR_PAIR(color_pair));
}

void	compute_size(t_board *board, int board_size)
{
	board->board_nrows = TILE_ROWS * (board_size + 1);
	board->board_nlines = TILE_LINES * (board_size + 1);
	board->term_nlines_min = board->board_nlines + 1;
	board->term_nrows_min = board->board_nrows + 17 + 1;
	board->board_size = board_size;
	board->free_tiles = board->board_size * board->board_size;
}
