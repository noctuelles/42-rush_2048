/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2048.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:16:16 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/19 19:55:52 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"
#include <string.h>
#include <ncurses.h>

bool	can_run_game(t_board *board)
{
	getmaxyx(stdscr, board->term_nlines, board->term_nrows);
	if (board->term_nlines < TERM_LINES_MIN || board->term_nrows < TERM_ROWS_MIN)
	{
		mvwaddstr(stdscr, 0, 0, STR_ATLEAST_SIZE);
		mvwaddstr(stdscr, 1, 0, STR_PRESS_KEY);
		getch();
		return (false);
	}
	return (true);
}

void	init_ncurses(void)
{
	initscr();
	noecho();
	raw();
	nonl();
	cbreak();
	keypad(stdscr, true);
}

void	init_game(t_board *board)
{
	memset(board, 0, sizeof(t_board));
	board->free_tiles = BOARD_SIZE * BOARD_SIZE;
}


int	main(void)
{
	t_board	board;
	int	ch;

	init_game(&board);
	init_ncurses();
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
		new_number(&board);
	if (can_run_game(&board) == true)
	{
		init_board_wnd(&board);
		while (1)
		{
			draw_board(&board);
			ch = getch();
			if (ch == KEY_RESIZE)
				getmaxyx(stdscr, board.term_nlines, board.term_nrows);
			else if (ch == 27)
				break ;
			else
			{
				if (ch == KEY_LEFT)
					move_left(&board);
				else if (ch == KEY_RIGHT)
					move_right(&board);
				else if (ch == KEY_UP)
					move_up(&board);
				else if (ch == KEY_DOWN)
					move_down(&board);
				for (int y = 0; y < BOARD_SIZE; y++)
				{
					for (int x=0; x < BOARD_SIZE; x++)
					{
						wclear(board.tiles[y][x].wnd);
					}
				}
			}
		}
	}
	delete_board_wnd(&board);
	endwin();
}
