/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_win_loose.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:01:08 by gusalle           #+#    #+#             */
/*   Updated: 2022/03/19 21:17:51 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"

unsigned int	check_win(t_board *board)
{
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board->tiles[y][x].value == WIN_VALUE)
				return (1);
		}
	}
	return (0);
}

unsigned int	check_lose(t_board *board)
{
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board->tiles[y][x].value == 0)
				return (0);
			if (y < BOARD_SIZE - 1
				&& board->tiles[y][x].value == board->tiles[y + 1][x].value)
				return (0);
			if (x < BOARD_SIZE - 1
				&& board->tiles[y][x].value == board->tiles[y][x + 1].value)
				return (0);
		}
	}
	return (1);
}
