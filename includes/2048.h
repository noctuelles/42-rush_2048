/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2048.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:16:53 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/20 17:11:58 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_2048
# define H_2048

# include <ncurses.h>
# include <stdlib.h>
# include <time.h>

/*******************************************************************************
 *                             Game define                                     *
 ******************************************************************************/

# define KEY_ESC        27

# define TILE_LINES     6
# define TILE_ROWS      12

# define PAIR_DEFAULT   1
# define PAIR_STEP_1    2
# define PAIR_STEP_2    3
# define PAIR_STEP_3    4
# define PAIR_STEP_4    5
# define PAIR_STEP_5    6

# define GAME_STOP_VALUE 2048

/*******************************************************************************
 *                             String define                                   *
 ******************************************************************************/

# define STR_ATLEAST_SIZE   "Your terminal must be at least %d lines by %d rows !"
# define STR_PLEASE_RESIZE  "Please resize your terminal to resume game."
# define STR_WIN_MSG        "You won ! Do you wanna continue ?"  
# define STR_LOSE_MSG       "You had no possible way to move."
# define STR_END_MSG        "You've reached 2048, the game ends here..."
# define STR_CHOICE         "Press UP for yes and DOWN for no."
# define STR_PRESS_KEY      "Press any key to exit..."

# define STR_GAME_TITLE     "-- 2048 Game --"
# define STR_SETUP_CHOICE_1 "1. Press UP to launch a 4x4 grid."
# define STR_SETUP_CHOICE_2 "2. Press DOWN to launch a 5x5 grid."
# define STR_SETUP_CHOICE_3 "3. Press ESC to exit the game."

/*******************************************************************************
 *                          Structure / Enum                                   *
 ******************************************************************************/

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
	t_tile			tiles[5][5];
	size_t			term_nlines;
	size_t			term_nlines_min;
	size_t			term_nrows;
	size_t			term_nrows_min;
	size_t			board_nlines;
	size_t			board_nrows;
	int				board_size;
	unsigned int	free_tiles;
	bool			won;
	unsigned int	win_value;
	unsigned int	color_pair;
}				t_board;

/*******************************************************************************
 *                          Functions                                          *
 ******************************************************************************/

/* board.c */

WINDOW *init_board_wnd(t_board *board);
void	delete_board_wnd(t_board *board);
void	draw_board(t_board *board);
void	wipe_tiles(t_board *board);

/* check_win_lose.c */

bool	check_win(t_board *board);
bool	check_max_value(t_board *board);
bool	check_lose(t_board *board);

/* rand.c */

void	new_number(t_board *board);

/* move_horizontal.c */

void	move_right(t_board *board);
void	move_left(t_board *board);

/* move_vertical.c */

void	move_up(t_board *board);
void	move_down(t_board *board);

/* display.c */

bool	display_setup_menu(t_board *board);
void	display_loosing_msg(void);
bool	display_winning_msg(void);
void	display_end_msg(void);

/* game_utils.c */

bool	is_power_of_two(int i);
void	set_color_pair(t_board *board, WINDOW *wnd, unsigned int color_pair);
void	compute_size(t_board *board, int board_size);

#endif
