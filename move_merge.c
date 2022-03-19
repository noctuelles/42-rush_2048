/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_merge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:34:42 by gusalle           #+#    #+#             */
/*   Updated: 2022/03/19 16:25:36 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"

static	move_left(t_tile *b) {
	for (int y=0; y < BOARD_SIZE; y++) {
		for (int x=0; x < BOARD_SIZE; x++) {
			if (b[y][x].value == 0) {
				for (int i=x; i < BOARD_SIZE; i++) {
					if (i < BOARD_SIZE - 1)
						b[y][i].value = b[y][i+1].value;
					else
						b[y][i] = 0;
				}
			}
			else if (x < BOARD_SIZE - 1 && b[y][x].value == b[y][x+1].value) {
				b[y][x].value *= 2;
				for (int i=x+1; i < BOARD_SIZE; i++) {
					if (i < BOARD_SIZE - 1)
						b[y][i].value = b[y][i+1].value;
					else
						b[y][i] = 0;
				}
			}
		}
	}
}

static	move_right(t_tile *b) {
	for (int y=0; y < BOARD_SIZE; y++) {
		for (int x = BOARD_SIZE-1; 0 <= x; x--) {
			if (b[y][x].value == 0) {
				for (int i=x; 0 <= i; i--) {
					if (0 < i)
						b[y][i].value = b[y][i-1].value;
					else
						b[y][i] = 0;
				}
			}
			else if (0 < x && b[y][x].value == b[y][x-1].value) {
				b[y][x].value *= 2;
				for (int i = x-1; 0 < i; i--) {
					if (0 < i)
						b[y][i].value = b[y][i-1].value;
					else
						b[y][i] = 0;
				}
			}
		}
	}
}

static	move_down(t_tile *b) {
	for (int x=0; y < BOARD_SIZE; y++) {
		for (int y=0; x < BOARD_SIZE; x++) {
			if (b[y][x].value == 0) {
				for (int i=x; i < BOARD_SIZE; i++) {
					if (i < BOARD_SIZE - 1)
						b[y][i].value = b[y][i+1].value;
					else
						b[y][i] = 0;
				}
			}
			else if (x < BOARD_SIZE - 1 && b[y][x].value == b[y][x+1].value) {
				b[y][x].value *= 2;
				for (int i=x+1; i < BOARD_SIZE; i++) {
					if (i < BOARD_SIZE - 1)
						b[y][i].value = b[y][i+1].value;
					else
						b[y][i] = 0;
				}
			}
		}
	}
}

static	move_down(t_tile *b) {
	for (int x=0; y < BOARD_SIZE; y++) {
		for (int y = BOARD_SIZE-1; 0 <= x; x--) {
			if (b[y][x].value == 0) {
				for (int i=x; 0 <= i; i--) {
					if (0 < i)
						b[y][i].value = b[y][i-1].value;
					else
						b[y][i] = 0;
				}
			}
			else if (0 < x && b[y][x].value == b[y][x-1].value) {
				b[y][x].value *= 2;
				for (int i = x-1; 0 < i; i--) {
					if (0 < i)
						b[y][i].value = b[y][i-1].value;
					else
						b[y][i] = 0;
				}
			}
		}
	}
}
void	move_and_merge(t_board *board, char *input) {
	t_tile	*b;

	b = board->tiles;
	if (ft_strcmp(input, "left") == 0)
		move_left(b);
	if (ft_strcmp(input, "right") == 0)
		move_right(b);
	if (ft_strcmp(input, "up") == 0)
		move_up(b);
	if (ft_strcmp(input, "down") == 0)
		move_down(b);
}
