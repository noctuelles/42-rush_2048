/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2048.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:16:53 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/20 13:46:37 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_2048
# define H_2048

# include <ncurses.h>
# include <stdlib.h>
# include <time.h>

# define BOARD_SIZE    5
# define KEY_ESC       27

# define TILE_LINES     6
# define TILE_ROWS      12
# define BOARD_ROWS     TILE_ROWS * (BOARD_SIZE + 1)
# define BOARD_LINES    TILE_LINES * (BOARD_SIZE + 1)

# define TERM_LINES_MIN (BOARD_LINES) + 1
# define TERM_ROWS_MIN  (BOARD_ROWS) + 1

# define STR_ATLEAST_SIZE   "Your terminal must be at least %d lines by %d rows !"
# define STR_PLEASE_RESIZE  "Please resize your terminal to resume game."
# define STR_WIN_MSG        "You won ! Do you wanna continue ?"  
# define STR_LOSE_MSG       "You loose ! You had no possible move."
# define STR_END_MSG        "You've reached 2048, the game ends here..."
# define STR_CHOICE         "Press UP for yes and DOWN for no."
# define STR_PRESS_KEY      "Press any key to exit..."

# define DEFAULT_WIN_VALUE 2048

enum	e_const
{
	WIN_VALUE = 32 
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
	unsigned int	free_tiles;
	bool			won;
	int				win_value;
}				t_board;


WINDOW *init_board_wnd(t_board *board);
void	delete_board_wnd(t_board *board);
void	draw_board(t_board *board);

bool	check_win(t_board *board);
bool	check_lose(t_board *board);
bool	check_max_value(t_board *board);

void			new_number(t_board *board);
void			move_and_merge(t_board *board, char *input);

void	move_right(t_board *board);
void	move_left(t_board *board);
void	move_up(t_board *board);
void	move_down(t_board *board);

void	wipe_tiles(t_board *board);

void	display_loosing_msg(void);
bool	display_winning_msg(void);
void	display_end_msg(void);

bool	is_power_of_two(int i);

#endif
