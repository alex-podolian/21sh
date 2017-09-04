/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_left_arrows.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opodolia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 20:01:30 by opodolia          #+#    #+#             */
/*   Updated: 2017/09/03 20:09:05 by opodolia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		move_right(void)
{
	if ((g_info->position) % g_info->win_size == 0 ||
		g_info->line[g_info->line_index] == '\n')
	{
		ft_putchar('\n');
		if (g_info->line[g_info->line_index] == '\n')
			extended_move_right(g_info->line_index, g_info->bytes_index);
	}
	else
		tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
	g_info->line_index += g_info->bytes_str[g_info->bytes_index++] - '0';
	g_info->position++;
//	ft_printf("\npos_1 = %d\n", g_info->position);
//	ft_printf("line_indx = %d\n", g_info->line_index);
//	ft_printf("byte_indx = %d\n", g_info->bytes_index);
}

void		move_left(void)
{
	int		tmp;
	int		line_indx;
	int		byte_indx;

	byte_indx = g_info->bytes_index - 1;
	line_indx = g_info->line_index - (g_info->bytes_str[byte_indx] - '0');
	if ((g_info->position - 1) % g_info->win_size == 0 ||
		g_info->line[line_indx] == '\n')
	{
		ft_putstr("\033M");
		if (g_info->line[line_indx] == '\n')
			extended_move_left(line_indx, byte_indx);
		else
		{
		//	ft_printf("\nhere\n");
			tmp = 0;
			while (tmp++ < g_info->win_size - 1)
				tputs(tgetstr("nd", 0), 1, &ft_put_my_char);
		}
	}
	else
		tputs(tgetstr("le", 0), 1, &ft_put_my_char);
	g_info->line_index -= g_info->bytes_str[--g_info->bytes_index] - '0';
	g_info->position--;
//	ft_printf("\npos_1 = %d\n", g_info->position);
//	ft_printf("line_indx = %d\n", g_info->line_index);
//	ft_printf("byte_indx = %d\n", g_info->bytes_index);
}

void		left_arrow(char *buf)
{
	if (buf[2] == LEFT && g_info->line_index > 0)
		move_left();
	else if (buf[3] == LEFT && g_info->line_index > 0)
	{
		while (g_info->line[g_info->line_index - 1] == ' ' &&
			g_info->line_index > 0)
			move_left();
		while (g_info->line[g_info->line_index - 1] != ' ' &&
			g_info->line_index > 0)
			move_left();
	}
	else if (buf[2] == START && g_info->line_index > 0)
		while (g_info->line_index > 0)
			move_left();
}

void		right_arrow(char *buf)
{
	if (buf[2] == RIGHT && g_info->line[g_info->line_index] &&
		g_info->bytes_str[g_info->bytes_index])
		move_right();
	else if (buf[3] == RIGHT && g_info->line[g_info->line_index])
	{
		while (g_info->line[g_info->line_index] != ' ' &&
			g_info->line_index < (int)ft_strlen(g_info->line))
			move_right();
		while (g_info->line[g_info->line_index] == ' ' &&
			g_info->line_index < (int)ft_strlen(g_info->line))
			move_right();
	}
	else if (buf[2] == END && g_info->line[g_info->line_index])
		while (g_info->line[g_info->line_index])
			move_right();
}
