/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2048.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:16:53 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/19 12:03:20 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_2048
# define H_2048

# include <ncurses.h>

# define BOARD_SIZE 4

typedef struct	s_tile
{
	WINDOW			*wnd;
	unsigned int	value;
}				t_tile;

typedef struct	s_board
{
	WINDOW			*wnd;
	t_tile			tiles[BOARD_SIZE][BOARD_SIZE];
	size_t			wnd_nlines;
	size_t			wnd_nrows;
	size_t			tile_nlines;
	size_t			tile_nrows;
	size_t			term_nlines;
	size_t			term_nrows;
	bool			re_draw;
}				t_board;

#endif
