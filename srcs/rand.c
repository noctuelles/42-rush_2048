/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:39:25 by gusalle           #+#    #+#             */
/*   Updated: 2022/03/20 16:52:54 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"

static unsigned int	random_number() {
	int	r;

	r = rand();
	if (r < RAND_MAX / 10)
		return (4);
	else
		return (2);
}

void	new_number(t_board *board) {
	int	r;
	
	if (board->free_tiles == 0)
		return ;
	r = rand();
	r = r / (RAND_MAX / board->free_tiles);
	for (int y = 0; y < board->board_size; y++)
	{
		for (int x = 0; x < board->board_size; x++)
		{
			if (board->tiles[y][x].value == 0)
				r--;
			if (r == -1) {
				board->tiles[y][x].value = random_number();
				board->free_tiles--;
				return ;
			}
		}
	}
}
