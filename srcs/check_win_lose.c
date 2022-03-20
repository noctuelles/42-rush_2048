/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_win_lose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:01:08 by gusalle           #+#    #+#             */
/*   Updated: 2022/03/20 16:32:33 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"

bool	check_win(t_board *board)
{
	for (int y = 0; y < board->board_size; y++)
	{
		for (int x = 0; x < board->board_size; x++)
		{
			if (board->tiles[y][x].value >= board->win_value)
				return (true);
		}
	}
	return (false);
}

bool	check_max_value(t_board *board)
{
	for (int y = 0; y < board->board_size; y++)
	{
		for (int x = 0; x < board->board_size; x++)
		{
			if (board->tiles[y][x].value == 2048)
				return (true);
		}
	}
	return (false);
}

bool	check_lose(t_board *board)
{
	for (int y = 0; y < board->board_size; y++)
	{
		for (int x = 0; x < board->board_size; x++)
		{
			if (board->tiles[y][x].value == 0)
				return (false);
			if (y < board->board_size - 1
				&& board->tiles[y][x].value == board->tiles[y + 1][x].value)
				return (false);
			if (x < board->board_size - 1
				&& board->tiles[y][x].value == board->tiles[y][x + 1].value)
				return (false);
		}
	}
	return (true);
}
