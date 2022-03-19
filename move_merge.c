/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_merge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:34:42 by gusalle           #+#    #+#             */
/*   Updated: 2022/03/19 19:05:52 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"

static void	move_left(t_board *board)
{
	unsigned int	value;
	unsigned int	i;

	for (int y=0; y < BOARD_SIZE; y++)
   	{
		for (int x=0; x < BOARD_SIZE; )
		{
			value = board->tiles[y][x].value;
			if (value == 0)
			{
				for (i = x + 1; i < BOARD_SIZE && board->tiles[y][i].value == 0; i++)
					;
				for (int k = 0; i + k < BOARD_SIZE; k++)
					board->tiles[y][x + k].value = board->tiles[y][i + k].value;
				if (i == BOARD_SIZE)
					x = BOARD_SIZE;
				continue;
			}
			for (i = x + 1; i < BOARD_SIZE; i++)
			{
				if (board->tiles[y][i].value == value)
					break;
				if (board->tiles[y][i].value != 0)
					i = BOARD_SIZE;
			}
			if (i < BOARD_SIZE)
			{
				board->tiles[y][x].value *= 2;
				board->tiles[y][i].value = 0;
				board->free_tiles++;
			}
			x++;
		}
	}
}

static void	move_right(t_board *board)
{
	unsigned int	value;
	unsigned int	i;

	for (int y=0; y < BOARD_SIZE; y++)
   	{
		for (int x = BOARD_SIZE - 1; 0 < x; )
		{
			value = board->tiles[y][x].value;
			if (value == 0)
			{
				for (i = x - 1; 0 <= i && board->tiles[y][i].value == 0; i--)
					;
				for (int k = 0; 0 <= i - k; k++)
					board->tiles[y][x - k].value = board->tiles[y][i - k].value;
				if (i < 0)
					x = -1;
				continue;
			}
			for (i = x - 1; 0 <= i; i--)
			{
				if (board->tiles[y][i].value == value)
					break;
				if (board->tiles[y][i].value != 0)
					i = -1;
			}
			if (0 <= i)
			{
				board->tiles[y][x].value *= 2;
				board->tiles[y][i].value = 0;
				board->free_tiles++;
			}
			x--;
		}
	}
}

static void	move_up(t_board *board)
{
	unsigned int	value;
	unsigned int	i;

	for (int x=0; x < BOARD_SIZE; x++)
   	{
		for (int y=0; y < BOARD_SIZE; )
		{
			value = board->tiles[y][x].value;
			if (value == 0)
			{
				for (i = x + 1; i < BOARD_SIZE && board->tiles[y][i].value == 0; i++)
					;
				for (int k = 0; i + k < BOARD_SIZE; k++)
					board->tiles[y][x + k].value = board->tiles[y][i + k].value;
				if (i == BOARD_SIZE)
					x = BOARD_SIZE;
				continue;
			}
			for (i = x + 1; i < BOARD_SIZE; i++)
			{
				if (board->tiles[y][i].value == value)
					break;
				if (board->tiles[y][i].value != 0)
					i = BOARD_SIZE;
			}
			if (i < BOARD_SIZE)
			{
				board->tiles[y][x].value *= 2;
				board->tiles[y][i].value = 0;
				board->free_tiles++;
			}
			y++;
		}
	}
}

static void	move_down(t_board *board)
{
	unsigned int	value;
	unsigned int	i;
	
	for (int x=0; x < BOARD_SIZE; x++)
   	{
		for (int y = BOARD_SIZE - 1; 0 < y; )
		{
			value = board->tiles[y][x].value;
			if (value == 0)
			{
				for (i = x - 1; 0 <= i && board->tiles[y][i].value == 0; i--)
					;
				for (int k = 0; 0 <= i - k; k++)
					board->tiles[y][x - k].value = board->tiles[y][i - k].value;
				if (i < 0)
					x = -1;
				continue;
			}
			for (i = x - 1; 0 <= i; i--)
			{
				if (board->tiles[y][i].value == value)
					break;
				if (board->tiles[y][i].value != 0)
					i = -1;
			}
			if (0 <= i)
			{
				board->tiles[y][x].value *= 2;
				board->tiles[y][i].value = 0;
				board->free_tiles++;
			}
			y--;
		}
	}
}

void	move_and_merge(t_board *board, char *input)
{
	if (ft_strcmp(input, "left") == 0)
		move_left(board);
	if (ft_strcmp(input, "right") == 0)
		move_right(board);
	if (ft_strcmp(input, "up") == 0)
		move_up(board);
	if (ft_strcmp(input, "down") == 0)
		move_down(board);
}
