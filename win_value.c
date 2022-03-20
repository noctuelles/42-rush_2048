/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 21:11:57 by gusalle           #+#    #+#             */
/*   Updated: 2022/03/19 21:12:00 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <2048.h>

bool	check_power(int n)
{
	int	i;

	for (i = 1; i < n; )
		i *= 2;
	if (i == n)
		return (1);
	else
		return (0);
}

void	win_value(t_board *board)
{
	if (check_power(WIN_VALUE))
		board->win_value = WIN_VALUE;
	else
		board_value = 2048;
}
