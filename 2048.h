/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2048.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:16:53 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/19 15:03:12 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_2048
# define H_2048

# include <ncurses.h>
# include <stdlib.h>
# include <time.h>

# define BOARD_SIZE 4

enum	e_const
{
	WIN_VALUE = 2048
};

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

unsigned int	check_win(t_board *board);
unsigned int	check_lose(t_board *board);
void			new_number(t_board *board);

#endif
