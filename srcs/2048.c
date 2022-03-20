/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2048.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:16:16 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/20 14:48:52 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"
#include <string.h>
#include <ncurses.h>
#include <signal.h>

int g_signo;

static bool	can_run_game(t_board *board)
{
	getmaxyx(stdscr, board->term_nlines, board->term_nrows);
	if (board->term_nlines < TERM_LINES_MIN || board->term_nrows < TERM_ROWS_MIN)
	{
		mvwprintw(stdscr, 0, 0, STR_ATLEAST_SIZE, TERM_LINES_MIN, TERM_ROWS_MIN);
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
	if (has_colors() == false)
	{
		delwin(stdscr);
		endwin();
		return (false);
	}
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	noecho();
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
	if (g_signo == SIGINT)
		return (false);
	if (board->won == false && check_win(board) == true)
	{
		if (display_winning_msg() == false)
			return (false);
		else
		{
			board->won = true;
			return (board->won);
		}
	}
	else if (check_lose(board) == true)
	{
		display_loosing_msg();
		return (false);
	}
	else if (check_max_value(board))
	{
		display_end_msg();
		return (false);
	}
	return (true);
}

void	catch_sigint(int signo)
{
	if (signo == SIGINT)
		g_signo = SIGINT;
}

int	main(void)
{
	t_board			board = {0};
	int				ch;

	if (signal(SIGINT, catch_sigint) == SIG_ERR)
		return (1);
	srand(time(NULL));
	init_game(&board);
	if (init_ncurses() == false)
		return (1);
	if (can_run_game(&board) == true)
	{
		if (init_board_wnd(&board) != NULL)
		{
			new_number(&board);
			new_number(&board);
			while (true)
			{
				if (can_continue(&board) == false)
					break ;
				draw_board(&board);
getkey:
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
					else
						goto getkey;
					new_number(&board);
					wipe_tiles(&board);
				}
			}
		}
	}
	delete_board_wnd(&board);
	delwin(stdscr);
	endwin();
	return (0);
}
