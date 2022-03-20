/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2048.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:16:16 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/20 15:55:11 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"
#include <string.h>
#include <ncurses.h>
#include <signal.h>

int g_signo;

static bool	can_run_game(t_board *board)
{
	int	ch;

	getmaxyx(stdscr, board->term_nlines, board->term_nrows);
	if (board->term_nlines < TERM_LINES_MIN || board->term_nrows < TERM_ROWS_MIN)
	{
		clear();
		mvwprintw(stdscr, 0, 0, STR_ATLEAST_SIZE, TERM_LINES_MIN, TERM_ROWS_MIN);
		mvwaddstr(stdscr, 1, 0, STR_PRESS_KEY);
getkey:
		ch = getch();
		if (ch == KEY_RESIZE)
			goto getkey;
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
	init_pair(PAIR_DEFAULT, COLOR_WHITE, COLOR_BLACK);
	init_pair(PAIR_STEP_1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(PAIR_STEP_2, COLOR_BLUE, COLOR_BLACK);
	init_pair(PAIR_STEP_3, COLOR_CYAN, COLOR_BLACK);
	init_pair(PAIR_STEP_4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(PAIR_STEP_5, COLOR_RED, COLOR_BLACK);
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

void	compute_size(t_board *board, size_t board_size)
{
	board->board_nrows = TILE_ROWS * (board_size + 1);
	board->board_nlines = TILE_LINES * (board_size + 1);
	board->term_nlines_min = board->board_nlines + 1;
	board->term_nrows_min = board->board_nrows + 17 + 1;
}

bool	setup_menu(t_board *board)
{
	int	ch;
	(void) board;

	while (1)
	{
		clear();
		attron(A_UNDERLINE);
		attron(A_BOLD);
		mvwaddstr(stdscr, 0, 7, "-- 2048 Game --");
		attroff(A_BOLD);
		attroff(A_UNDERLINE);
		attron(A_REVERSE);
		mvwaddstr(stdscr, 2, 0, "1. Press UP to launch a 4x4 grid.");
		mvwaddstr(stdscr, 4, 0, "2. Press DOWN to launch a 5x5 grid.");
		attroff(A_REVERSE);
		mvwaddstr(stdscr, 6, 0, "3. Press ESC to exit the game.");
		ch = getch();
		if (ch == KEY_UP)
		{
			return (true);
		}
		else if (ch == KEY_DOWN)
		{
			return (true);
		}
		else if (ch == KEY_ESC)
			return (false);
	}
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
	if (setup_menu(&board) == true)
	{
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
	}
	delete_board_wnd(&board);
	delwin(stdscr);
	endwin();
	return (0);
}
