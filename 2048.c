/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2048.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:16:16 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/20 12:48:29 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"
#include <string.h>
#include <ncurses.h>

static bool	can_run_game(t_board *board)
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

static bool	init_ncurses(void)
{
	if (initscr() == NULL)
		return (false);
	noecho();
	raw();
	curs_set(0);
	nonl();
	cbreak();
	keypad(stdscr, true);
	return (true);
}

static void	init_game(t_board *board)
{
	if (WIN_VALUE > 2147483647 || WIN_VALUE < 2 || is_power_of_two(WIN_VALUE) == false)
		board->win_value = DEFAULT_WIN_VALUE;
	else
		board->win_value = WIN_VALUE;
	board->free_tiles = BOARD_SIZE * BOARD_SIZE;
}

static bool	can_continue(t_board *board)
{
	if (board->won == false && check_win(board) == true)
	{
		if (display_winning_msg(board) == false)
			return (false);
		else
		{
			board->won = true;
			return (board->won);
		}
	}
	else if (check_lose(board) == true)
	{
		display_loosing_msg(board);
		return (false);
	}
	return (true);
}

int	main(void)
{
	t_board			board = {0};
	int				ch;

	srand(time(NULL));
	init_game(&board);
	if (init_ncurses() == false)
		return (1);
	if (can_run_game(&board) == true)
	{
		init_board_wnd(&board);
		new_number(&board);
		new_number(&board);
		while (1)
		{
			if (can_continue(&board) == false)
				break ;
			draw_board(&board);
			ch = getch();
			if (ch == KEY_RESIZE)
				getmaxyx(stdscr, board.term_nlines, board.term_nrows);
			else if (ch == KEY_ESC)
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
				new_number(&board);
				wipe_tiles(&board);
			}
		}
	}
	delete_board_wnd(&board);
	endwin();
}
