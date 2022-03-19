/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2048.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:16:16 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/19 15:57:44 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"
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

int	main(void)
{
	t_board	board = {0};
	int	ch;

	init_ncurses();
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
			{
				break ;
			}
		}
	}
	delete_board_wnd(&board);
	endwin();
}
