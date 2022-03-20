/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:25:26 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/19 20:14:10 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"

static void	merge_up(t_board *board)
{
	for (int x = 0; x < board->board_size; x++)
	{
		for (int y = 0; y < board->board_size; y++)
		{
			if (board->tiles[y][x].value != 0)
			{
				for (int yi = y + 1; yi < board->board_size; yi++)
				{
					if (board->tiles[yi][x].value == 0)
						continue;
					else if (board->tiles[yi][x].value != board->tiles[y][x].value)
						break ;
					else
					{
						board->tiles[y][x].value *= 2;
						board->tiles[yi][x].value = 0;
						board->free_tiles++;
						break ;
					}
				}
			}
		}
	}
}

void	move_up(t_board *board)
{
	merge_up(board);
	for (int x = 0; x < board->board_size; x++)
	{
		for (int y = 0; y < board->board_size; y++)
		{
			if (board->tiles[y][x].value == 0)
			{
				for (int yi = y + 1; yi < board->board_size; yi++)
				{
					if (board->tiles[yi][x].value != 0)
					{
						board->tiles[y][x].value = board->tiles[yi][x].value;
						board->tiles[yi][x].value = 0;
						break ;
					}
				}
			}
		}
	}
}
static void	merge_down(t_board *board)
{
	for (int x = 0; x < board->board_size; x++)
	{
		for (int y = board->board_size - 1; y >= 0; y--)
		{
			if (board->tiles[y][x].value != 0)
			{
				for (int yi = y - 1; yi >= 0; yi--)
				{
					if (board->tiles[yi][x].value == 0)
						continue;
					else if (board->tiles[yi][x].value != board->tiles[y][x].value)
						break ;
					else
					{
						board->tiles[y][x].value *= 2;
						board->tiles[yi][x].value = 0;
						board->free_tiles++;
						break ;
					}
				}
			}
		}
	}
}

void	move_down(t_board *board)
{
	merge_down(board);
	for (int x = 0; x < board->board_size; x++)
	{
		for (int y = board->board_size - 1; y >= 0; y--)
		{
			if (board->tiles[y][x].value == 0)
			{
				for (int yi = y - 1; yi >= 0; yi--)
				{
					if (board->tiles[yi][x].value != 0)
					{
						board->tiles[y][x].value = board->tiles[yi][x].value;
						board->tiles[yi][x].value = 0;
						break ;
					}
				}
			}
		}
	}
}
