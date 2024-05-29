/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:42:58 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/02/25 21:43:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "bsq.h"
#include "ft_str_nbr.h"

void	print_matrix(t_map *map)
{
	int		l;
	int		c;
	t_mtxn	*matrix;

	matrix = map->matrix;
	l = 0;
	while (l < map->nblines)
	{
		c = 0;
		while (c < map->width)
		{
			ft_putnbr(*matrix++);
			write(1, " ", 1);
			c++;
		}
		ft_putstr(0, true);
		l++;
	}
}

void	fill_map(t_map *map)
{
	int	l;
	int	c;

	if (map->sol_size == 0)
		return ;
	l = map->sol_line0;
	while (l <= map->sol_line1)
	{
		c = map->sol_x0;
		while (c <= map->sol_x1)
		{
			map->lines[l][c] = map->chr_fill;
			c++;
		}
		l++;
	}
}

void	print_map(t_map *map)
{
	const bool	prn_space = map->cf.dbg_flags & DBG_PRN_SPC;
	int			l;
	int			c;

	l = 0;
	while (l < map->nblines)
	{
		if (prn_space)
		{
			c = 0;
			while (c < map->width)
			{
				write(1, &map->lines[l][c], 1);
				write(1, " ", 1);
				c++;
			}
		}
		else
			print(map->lines[l]);
		ft_putchar('\n');
		l++;
	}
}

void	print_sol_coord(t_map *map)
{
	if (map->sol_size == 0)
		ft_printf("Zero solution !\n");
	else
		ft_printf("Solution: (%i,%i)-(%i,%i)  size = %i\n", map->sol_x0,
			map->sol_line0, map->sol_x1, map->sol_line1, map->sol_size);
}

void	print_solution(t_map *map)
{
	if (map->cf.dbg_flags & DBG_PRN_RAWSOL)
		print_sol_coord(map);
	else
	{
		fill_map(map);
		print_map(map);
		if (map->cf.dbg_flags & DBG_VERBOSE)
			print_sol_coord(map);
	}
}
