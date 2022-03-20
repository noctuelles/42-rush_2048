/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 12:39:44 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/20 15:05:26 by plouvel          ###   ########.fr       */
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
