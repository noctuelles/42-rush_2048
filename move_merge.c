/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_merge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:34:42 by gusalle           #+#    #+#             */
/*   Updated: 2022/03/19 18:50:43 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"

static void	move_left(t_tile b[BOARD_SIZE][BOARD_SIZE])
{
	unsigned int	value;
	unsigned int	i;

	for (int y=0; y < BOARD_SIZE; y++)
   	{
		for (int x=0; x < BOARD_SIZE; )
		{
			value = b[y][x].value;
			if (value == 0)
			{
				for (i = x + 1; i < BOARD_SIZE && b[y][i].value == 0; i++)
					;
				for (int k = 0; i + k < BOARD_SIZE; k++)
					b[y][x + k].value = b[y][i + k].value;
				if (i == BOARD_SIZE)
					x = BOARD_SIZE;
				continue;
			}
			for (i = x + 1; i < BOARD_SIZE; i++)
			{
				if (b[y][i].value == value)
					break;
				if (b[y][i].value != 0)
					i = BOARD_SIZE;
			}
			if (i < BOARD_SIZE)
			{
				b[y][x].value *= 2;
				b[y][i].value = 0;
			}
			x++;
		}
	}
}

static void	move_right(t_tile b[BOARD_SIZE][BOARD_SIZE])
{
	unsigned int	value;
	unsigned int	i;

	for (int y=0; y < BOARD_SIZE; y++)
   	{
		for (int x = BOARD_SIZE - 1; 0 < x; )
		{
			value = b[y][x].value;
			if (value == 0)
			{
				for (i = x - 1; 0 <= i && b[y][i].value == 0; i--)
					;
				for (int k = 0; 0 <= i - k; k++)
					b[y][x - k].value = b[y][i - k].value;
				if (i < 0)
					x = -1;
				continue;
			}
			for (i = x - 1; 0 <= i; i--)
			{
				if (b[y][i].value == value)
					break;
				if (b[y][i].value != 0)
					i = -1;
			}
			if (0 <= i)
			{
				b[y][x].value *= 2;
				b[y][i].value = 0;
			}
			x--;
		}
	}
}

static void	move_up(t_tile b[BOARD_SIZE][BOARD_SIZE])
{
	unsigned int	value;
	unsigned int	i;

	for (int x=0; x < BOARD_SIZE; x++)
   	{
		for (int y=0; y < BOARD_SIZE; )
		{
			value = b[y][x].value;
			if (value == 0)
			{
				for (i = x + 1; i < BOARD_SIZE && b[y][i].value == 0; i++)
					;
				for (int k = 0; i + k < BOARD_SIZE; k++)
					b[y][x + k].value = b[y][i + k].value;
				if (i == BOARD_SIZE)
					x = BOARD_SIZE;
				continue;
			}
			for (i = x + 1; i < BOARD_SIZE; i++)
			{
				if (b[y][i].value == value)
					break;
				if (b[y][i].value != 0)
					i = BOARD_SIZE;
			}
			if (i < BOARD_SIZE)
			{
				b[y][x].value *= 2;
				b[y][i].value = 0;
			}
			y++;
		}
	}
}

static void	move_down(t_tile b[BOARD_SIZE][BOARD_SIZE])
{
	unsigned int	value;
	unsigned int	i;

	for (int x=0; x < BOARD_SIZE; x++)
   	{
		for (int y = BOARD_SIZE - 1; 0 < y; )
		{
			value = b[y][x].value;
			if (value == 0)
			{
				for (i = x - 1; 0 <= i && b[y][i].value == 0; i--)
					;
				for (int k = 0; 0 <= i - k; k++)
					b[y][x - k].value = b[y][i - k].value;
				if (i < 0)
					x = -1;
				continue;
			}
			for (i = x - 1; 0 <= i; i--)
			{
				if (b[y][i].value == value)
					break;
				if (b[y][i].value != 0)
					i = -1;
			}
			if (0 <= i)
			{
				b[y][x].value *= 2;
				b[y][i].value = 0;
			}
			y--;
		}
	}
}

void	move_and_merge(t_board *board, char *input)
{
	if (ft_strcmp(input, "left") == 0)
		move_left(board->tiles);
	if (ft_strcmp(input, "right") == 0)
		move_right(board->tiles);
	if (ft_strcmp(input, "up") == 0)
		move_up(board->tiles);
	if (ft_strcmp(input, "down") == 0)
		move_down(board->tiles);
}
