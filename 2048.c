/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2048.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:16:16 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/19 13:36:34 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"
#include <ncurses.h>

void	init_game(t_board *board)
{
	board->wnd = newwin(board->wnd_nlines,
			board->wnd_nrows,
			0,
			0);
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			board->tiles[y][x].wnd = subwin(board->wnd,
					board->tile_nlines,
					board->tile_nrows,
					3 + y * (board->tile_nlines),
					4 + x * (board->tile_nrows));
		}
	}
}

void	draw_game(t_board *board)
{
	refresh();
	box(board->wnd, ACS_VLINE, ACS_HLINE);
	wrefresh(board->wnd);
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			box(board->tiles[y][x].wnd, ACS_VLINE, ACS_HLINE);
			touchwin(board->wnd);
			wrefresh(board->tiles[y][x].wnd);
		}
	}
}

void	delete_game(t_board *board)
{
	for (int y = 0; y < BOARD_SIZE; y++)
	{
		for (int x = 0; x < BOARD_SIZE; x++)
			delwin(board->tiles[y][x].wnd);
	}
	delwin(board->wnd);
}

bool	can_run_game(void)
{
	size_t	term_nlines;
	size_t	term_nrows;

	getmaxyx(stdscr, term_nlines, term_nrows);
	if (term_nlines < 26 || term_nrows < 71)
	{
		mvwaddstr(stdscr, 0, 0, "Your terminal must be at least 71x26 !");
		mvwaddstr(stdscr, 1, 0, "Press any key to exit...");
		return (false);
	}
	return (true);
}

int	main(void)
{
	t_board	board;
	int	ch;

	board.tile_nlines = 5;
	board.tile_nrows = 10;
	board.wnd_nlines = board.tile_nlines * 5 + 1;
	board.wnd_nrows = board.tile_nrows * 5;

	initscr();
	noecho();
	raw();
	cbreak();
	keypad(stdscr, true);
	if (can_run_game() == true)
	{
		init_game(&board);
	}
	while (1)
	{
		draw_game(&board);
		ch = getch();
		if (ch == KEY_RESIZE)
		{
			size_t	term_nlines;
			size_t	term_nrows;

			getmaxyx(stdscr, board.term_nlines, board.term_nrows);
		}
	}
	delete_game(&board);
	endwin();
}
