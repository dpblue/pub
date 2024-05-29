/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hucherea & ade-sarr                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:38:56 by hucherea          #+#    #+#             */
/*   Updated: 2024/03/10 15:35:32 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include "ft_str_nbr.h"
#include <unistd.h>
#include <stdlib.h>

/* Alloue le buffer de lecture du fichier de map
 * alloue le tableau de char * map->lines
 * alloue la mémoire pour la première ligne (taille initiale: MAP_WITH_INIT)
 * Renvoie le buffer de lecture
*/
char	*setup_read_map(t_map *map)
{
	int	i;

	map->filebuffer = malloc(map->cf.file_buffer_size);
	if (!map->filebuffer)
		memory_error(map);
	if (map->cf.dbg_flags & DBG_VERBOSE)
		ft_printf("[setup_read_map] buffer size = %i\n",
			map->cf.file_buffer_size);
	map->lines = (char **)malloc(map->nblines * sizeof(char *));
	if (!map->lines)
		memory_error(map);
	i = 0;
	while (i < map->nblines)
		map->lines[i++] = NULL;
	map->nline = -1;
	map->width = MAP_WIDTH_INIT;
	alloc_nextline(map);
	return (map->filebuffer);
}

/* read_map doit etre appelé avec une struc map où les champs nblines,
 * chr_empty, chr_obst, chr_fill ont déjà été renseignés (init_map se charge
 * de cela). Renvoie true si ok et false si erreur.
 * NB: Precedemment le dernier return était: return (false); modifié pour
 * renvoyer true meme si le fichier ne comporte pas de retour à la ligne final.
*/
bool	read_map(t_map *map, int fdesc)
{
	const int	bufsize = map->cf.file_buffer_size;
	char		*buffer;
	int			nb_read;
	int			retfill;

	buffer = setup_read_map(map);
	nb_read = read(fdesc, buffer, bufsize);
	while (nb_read > 0)
	{
		retfill = fill_lines(map, buffer, nb_read);
		if (retfill == FILL_LINES_ERROR)
			return (false);
		if (retfill == FILL_LINES_COMPLETED)
			return (true);
		nb_read = read(fdesc, buffer, bufsize);
	}
	return (map->nline + 1 == map->nblines && map->linelen == map->width);
}
