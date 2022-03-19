/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2048.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:16:53 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/19 16:27:51 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_2048
# define H_2048

# include <ncurses.h>
# include <stdlib.h>
# include <time.h>

# define BOARD_SIZE 4

<<<<<<< HEAD
# define TERM_LINES_MIN 31
# define TERM_ROWS_MIN  84 

# define TILE_LINES  6
# define TILE_ROWS   12
# define BOARD_ROWS  TILE_ROWS * (BOARD_SIZE + 1)
# define BOARD_LINES TILE_LINES * (BOARD_SIZE + 1)

# define STR_ATLEAST_SIZE   "Your terminal must be at least 110x31"
# define STR_PLEASE_RESIZE  "Please resize your terminal to resume game."
# define STR_PRESS_KEY      "Press any key to exit..."

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
	size_t			term_nlines;
	size_t			term_nrows;
}				t_board;


void	init_board_wnd(t_board *board);
void	delete_board_wnd(t_board *board);
void	draw_board(t_board *board);
unsigned int	check_win(t_board *board);
unsigned int	check_lose(t_board *board);
	bool			re_draw;
	unsigned int	free_tiles;
}				t_board;

unsigned int	check_win(t_board *board);
unsigned int	check_lose(t_board *board);
void			new_number(t_board *board);
void			move_and_merge(t_board *board, char *input);

#endif
