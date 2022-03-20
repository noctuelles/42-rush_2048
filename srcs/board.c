/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:26:23 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/20 15:46:17 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"

WINDOW	*init_board_wnd(t_board *board)
{
	board->wnd = newwin(BOARD_LINES,
			BOARD_ROWS,
			0,
			0);
	if (board->wnd == NULL)
		return (NULL);
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			board->tiles[y][x].wnd = subwin(board->wnd,
					TILE_LINES,
					TILE_ROWS,
					3 + y * TILE_LINES,
					6 + x * TILE_ROWS);
			if (board->tiles[y][x].wnd == NULL)
			{
				delete_board_wnd(board);
				return (NULL);
			}
		}
	}
	return (board->wnd);
}

void	delete_board_wnd(t_board *board)
{
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board->tiles[y][x].wnd != NULL)
			{
				delwin(board->tiles[y][x].wnd);
				board->tiles[y][x].wnd = NULL;
			}
		}
	}
	delwin(board->wnd);
	board->wnd = NULL;
}

void	wipe_tiles(t_board *board)
{
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x=0; x < BOARD_SIZE; x++)
		{
			wclear(board->tiles[y][x].wnd);
		}
	}
}

static void	stall_mode(t_board *board)
{
	int	ch;

	delete_board_wnd(board);
	while (board->term_nlines < TERM_LINES_MIN || board->term_nrows < TERM_ROWS_MIN)
	{
		clear();
		mvwprintw(stdscr, 0, 0, STR_ATLEAST_SIZE, TERM_LINES_MIN, TERM_ROWS_MIN);
		mvwaddstr(stdscr, 1, 0, STR_PLEASE_RESIZE);
		ch = getch();
		if (ch == KEY_RESIZE)
			getmaxyx(stdscr, board->term_nlines, board->term_nrows);
		else if (ch == KEY_ESC)
		{
			delwin(stdscr);
			endwin();
			exit_curses(0);
		}
	}
	init_board_wnd(board);
}

bool	display_winning_msg(void)
{
	int	ch;

	while (true)
	{
		clear();
		mvwaddstr(stdscr, 0, 0, STR_WIN_MSG);
		mvwaddstr(stdscr, 1, 0, STR_CHOICE);
		ch = getch();
		if (ch == KEY_UP)
			return (true);
		else if (ch == KEY_DOWN)
			return (false);
		else if (ch == KEY_ESC)
			return (false);
	}
}

void	draw_board(t_board *board)
{
	if (board->term_nlines < TERM_LINES_MIN || board->term_nrows < TERM_ROWS_MIN)
		stall_mode(board);

	attron(A_UNDERLINE);
	attron(A_BOLD);
	mvwaddstr(stdscr, 1, BOARD_ROWS + 3, "-- 2048 Game --");
	attroff(A_BOLD);
	mvwaddstr(stdscr, 3, BOARD_ROWS + 2, "plouvel & gusalle"); 
	attroff(A_UNDERLINE);

	mvwprintw(stdscr, 5, BOARD_ROWS + 2, "Win value : %u", board->win_value); 
	refresh();
	wattron(board->wnd, A_REVERSE);
	box(board->wnd, ACS_VLINE, ACS_HLINE);
	wattroff(board->wnd, A_REVERSE);
	wrefresh(board->wnd);
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			if (board->tiles[y][x].value == 0)
				set_color_pair(board, board->tiles[y][x].wnd, PAIR_DEFAULT);
			else if (board->tiles[y][x].value == 2)
				set_color_pair(board, board->tiles[y][x].wnd, PAIR_STEP_1);
			else if (board->tiles[y][x].value <= 16)
				set_color_pair(board, board->tiles[y][x].wnd, PAIR_STEP_2);
			else if (board->tiles[y][x].value <= 32)
				set_color_pair(board, board->tiles[y][x].wnd, PAIR_STEP_3);
			else if (board->tiles[y][x].value <= 64)
				set_color_pair(board, board->tiles[y][x].wnd, PAIR_STEP_4);
			else
				set_color_pair(board, board->tiles[y][x].wnd, PAIR_STEP_5);
			box(board->tiles[y][x].wnd, ACS_VLINE, ACS_HLINE);
			wattroff(board->tiles[y][x].wnd, board->color_pair);
			if (board->tiles[y][x].value != 0)
			{
				mvwprintw(board->tiles[y][x].wnd,
						TILE_LINES / 2,
						1,
						"%d",
						board->tiles[y][x].value);
			}
			touchwin(board->wnd);
			wrefresh(board->tiles[y][x].wnd);
		}
	}
}

void	display_loosing_msg(void)
{
	int	ch;

	clear();
	mvwaddstr(stdscr, 0, 0, STR_LOSE_MSG);
	mvwaddstr(stdscr, 1, 0, STR_PRESS_KEY);
getkey:
	ch = getch();
	if (ch == KEY_RESIZE)
		goto getkey;
}

void	display_end_msg(void)
{
	int	ch;

	clear();
	mvwaddstr(stdscr, 0, 0, STR_END_MSG);
	mvwaddstr(stdscr, 1, 0, STR_PRESS_KEY);
getkey:
	ch = getch();
	if (ch == KEY_RESIZE)
		goto getkey;
}
