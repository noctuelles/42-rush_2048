/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:39:25 by gusalle           #+#    #+#             */
/*   Updated: 2022/03/19 15:03:30 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"

static unsigned int	random_number() {
	int	r

	r = rand();
	if (r < RAND_MAX / 10)
		return (4);
	else
		return (2);
}

void	new_number(t_board *board) {
	int	r;
	
	r = rand();
	r = r / (RAND_MAX / board->free_tiles);
	for (int y=0; y < BOARD_SIZE; y++) {
		for (int x=0; x < BOARD_SIZE; x++) {
			if (board->tiles[x][y].value == 0)
				r--;
			if (r == -1) {
				board->tiles[x][y].value = random_number();
				return ;
			}
		}
	}
}
