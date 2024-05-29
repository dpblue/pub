/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr & hucherea                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 22:00:30 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/02/25 22:00:33 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bsq.h"

t_mtxn	ft_min(t_mtxn a, t_mtxn b, t_mtxn c)
{
	if (b < a)
		a = b;
	if (c < a)
		a = c;
	return (a);
}

t_mtxn	save_solution(t_map *map, int c, int l, t_mtxn sol_size)
{
	map->sol_size = sol_size;
	map->sol_line1 = l;
	map->sol_x1 = c;
	return (sol_size);
}

int	compute_matrix(t_map *map, t_mtxn *mtx)
{
	const int	width = map->width;
	const int	nblines = map->nblines;
	int			l;
	int			c;
	t_mtxn		maxval;

	maxval = map->sol_size;
	mtx += width;
	l = 0;
	while (++l < nblines)
	{
		mtx++;
		c = 0;
		while (++c < width)
		{
			if (*mtx != 0)
			{
				*mtx = ft_min(mtx[-1], mtx[-1 - width], mtx[-width]) + 1;
				if (*mtx > maxval)
					maxval = save_solution(map, c, l, *mtx);
			}
			mtx++;
		}
	}
	return (maxval);
}

void	setup_matrix(t_map *map, t_mtxn *matrix, char **lines)
{
	const char	*line = *map->lines;
	const char	obst = map->chr_obst;
	const int	width = map->width;
	int			c;
	int			l;

	l = 0;
	while (l < map->nblines)
	{
		line = lines[l];
		c = 0;
		while (c < width)
		{
			if (line[c] == obst)
				*matrix++ = 0;
			else
				*matrix++ = 1;
			if (map->sol_size == 0 && matrix[-1] > 0)
				save_solution(map, c, l, 1);
			c++;
		}
		l++;
	}
}

int	find_solution(t_map *map)
{
	map->matrix = malloc(map->width * map->nblines * sizeof(t_mtxn));
	if (!map->matrix)
		memory_error(map);
	map->sol_size = 0;
	setup_matrix(map, map->matrix, map->lines);
	compute_matrix(map, map->matrix);
	map->sol_line0 = map->sol_line1 - map->sol_size + 1;
	map->sol_x0 = map->sol_x1 - map->sol_size + 1;
	if (map->cf.dbg_flags & DBG_MATRIX)
		print_matrix(map);
	ft_free((void **)&map->matrix);
	return (map->sol_size);
}
