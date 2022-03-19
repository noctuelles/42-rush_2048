/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:26:23 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/19 23:29:26 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"

void	init_board_wnd(t_board *board)
{
	board->wnd = newwin(BOARD_LINES,
			BOARD_ROWS,
			0,
			0);
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			board->tiles[y][x].wnd = subwin(board->wnd,
					TILE_LINES,
					TILE_ROWS,
					3 + y * TILE_LINES,
					6 + x * TILE_ROWS);
		}
	}
}

void	delete_board_wnd(t_board *board)
{
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
			delwin(board->tiles[y][x].wnd);
	}
	delwin(board->wnd);
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
		mvwaddstr(stdscr, 0, 0, STR_ATLEAST_SIZE);
		mvwaddstr(stdscr, 1, 0, STR_PLEASE_RESIZE);
		ch = getch();
		if (ch == KEY_RESIZE)
			getmaxyx(stdscr, board->term_nlines, board->term_nrows);
	}
	init_board_wnd(board);
}

bool	display_winning_msg(t_board *board)
{
	int	ch;

	while (true)
	{
		clear();
		mvwaddstr(stdscr, 0, 0, "You won ! Do you wanna continue ?");
		mvwaddstr(stdscr, 1, 0, "Press UP for yes and DOWN for no.");
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
	mvwaddstr(stdscr, 0, 65, "2048 Game");
	refresh();
	box(board->wnd, ACS_VLINE, ACS_HLINE);
	wrefresh(board->wnd);
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			box(board->tiles[y][x].wnd, ACS_VLINE, ACS_HLINE);
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

void	display_loosing_msg(t_board *board)
{
	int	ch;

	clear();
	mvwaddstr(stdscr, 0, 0, "You loose ! You had no possible move.");
	mvwaddstr(stdscr, 1, 0, STR_PRESS_KEY);
	ch = getch();
}
