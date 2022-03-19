/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:15:19 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/19 19:22:32 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"

static void	merge_left(t_board *board)
{
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board->tiles[y][x].value != 0)
			{
				for (int xi = x + 1; xi < BOARD_SIZE; xi++)
				{
					if (board->tiles[y][xi].value == 0)
						continue;
					else if (board->tiles[y][xi].value != board->tiles[y][x].value)
						break ;
					else
					{
						board->tiles[y][x].value *= 2;
						board->tiles[y][xi].value = 0;
						break ;
					}
				}
			}
		}
	}
}

void	move_left(t_board *board)
{
	merge_left(board);
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board->tiles[y][x].value == 0)
			{
				for (int xi = x + 1; xi < BOARD_SIZE; xi++)
				{
					if (board->tiles[y][xi].value != 0)
					{
						board->tiles[y][x].value = board->tiles[y][xi].value;
						board->tiles[y][xi].value = 0;
						break ;
					}
				}
			}
		}
	}
}

static void	merge_right(t_board *board)
{
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = BOARD_SIZE - 1; x >= 0; x--)
		{
			if (board->tiles[y][x].value != 0)
			{
				for (int xi = x - 1; xi >= 0; xi--)
				{
					if (board->tiles[y][xi].value == 0)
						continue;
					else if (board->tiles[y][xi].value != board->tiles[y][x].value)
						break ;
					else
					{
						board->tiles[y][x].value *= 2;
						board->tiles[y][xi].value = 0;
						break ;
					}
				}
			}
		}
	}
}

void	move_right(t_board *board)
{
	merge_right(board);
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = BOARD_SIZE - 1; x >= 0; x--)
		{
			if (board->tiles[y][x].value == 0)
			{
				for (int xi = x - 1; xi >= 0; xi--)
				{
					if (board->tiles[y][xi].value != 0)
					{
						board->tiles[y][x].value = board->tiles[y][xi].value;
						board->tiles[y][xi].value = 0;
						break ;
					}
				}
			}
		}
	}
}
