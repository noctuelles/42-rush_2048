/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2048.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:16:16 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/20 17:52:55 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"
#include <string.h>
#include <ncurses.h>
#include <signal.h>

static bool	can_run_game(t_board *board)
{
	int	ch;

	getmaxyx(stdscr, board->term_nlines, board->term_nrows);
	if (board->term_nlines < board->term_nlines_min
			|| board->term_nrows < board->term_nrows_min)
	{
		while (1)
		{
			clear();
			mvwprintw(stdscr, 0, 0, STR_ATLEAST_SIZE,
					board->term_nrows_min, board->term_nlines_min);
			mvwaddstr(stdscr, 1, 0, STR_PRESS_KEY);
			ch = getch();
			if (ch != KEY_RESIZE)
				return (false);
		}
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
	if (WIN_VALUE > 2147483647 || WIN_VALUE < 1
			|| is_power_of_two(WIN_VALUE) == false)
		board->win_value = GAME_STOP_VALUE;
	else
		board->win_value = WIN_VALUE;
}

static bool	can_continue(t_board *board)
{
	if (board->won == false && check_win(board) == true)
	{
		if (check_max_value(board) == true)
		{
			display_winning_msg();
			display_end_msg();
			return (false);
		}
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

int	main(void)
{
	t_board			board = {0};
	int				ch;

	srand(time(NULL));
	init_game(&board);
	if (init_ncurses() == false)
		return (1);
	if (display_setup_menu(&board) == true)
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
					getmaxyx(stdscr, board.term_nlines, board.term_nrows);
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
