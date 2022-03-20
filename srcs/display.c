/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:12:22 by plouvel           #+#    #+#             */
/*   Updated: 2022/03/20 16:56:11 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2048.h"
#include <signal.h>

bool	display_setup_menu(t_board *board)
{
	int	ch;

	while (1)
	{
		clear();
		attron(A_UNDERLINE);
		attron(A_BOLD);
		mvwaddstr(stdscr, 0, 7, STR_GAME_TITLE);
		attroff(A_BOLD);
		attroff(A_UNDERLINE);
		attron(A_REVERSE);
		mvwaddstr(stdscr, 2, 0, STR_SETUP_CHOICE_1);
		mvwaddstr(stdscr, 4, 0, STR_SETUP_CHOICE_2);
		attroff(A_REVERSE);
		mvwaddstr(stdscr, 6, 0, STR_SETUP_CHOICE_3);
		ch = getch();
		if (ch == KEY_UP)
		{
			compute_size(board, 4);
			return (true);
		}
		else if (ch == KEY_DOWN)
		{
			compute_size(board, 5);
			return (true);
		}
		else if (ch == KEY_ESC)
			return (false);
	}
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
