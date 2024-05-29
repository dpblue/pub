/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:17:23 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/02/28 15:52:42 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bsq.h"
#include "ft_str_nbr.h"

void	ft_free(void **pptr)
{
	if (*pptr)
	{
		free(*pptr);
		*pptr = NULL;
	}
}

void	free_map(t_map **pmap)
{
	const t_map	*map = *pmap;
	int			i;

	if (!map)
		return ;
	i = 0;
	if (map->lines)
	{
		while (i < map->nblines && map->lines[i])
			free(map->lines[i++]);
		free(map->lines);
	}
	if (map->matrix)
		free(map->matrix);
	if (map->filebuffer)
		free(map->filebuffer);
	free((void *)map);
	*pmap = NULL;
}

void	memory_error(t_map *map)
{
	ft_puterrmsg("memory error : malloc failed !");
	free_map(&map);
	exit(1);
}
