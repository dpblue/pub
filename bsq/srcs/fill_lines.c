/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr                                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:38:56 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/10 15:35:32 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include "ft_str_nbr.h"
#include <stdlib.h>

/* S'il reste des lignes à lire on alloue de la mémoire pour la ligne
 * suivante, on MAJ: nline, linelen, pline et on renvoie true.
 * Sinon (toutes les lignes ont été lues), on renvoie false.
*/
bool	alloc_nextline(t_map *map)
{
	if (map->nline + 1 >= map->nblines)
		return (false);
	map->nline++;
	map->line = malloc((map->width + 1) * sizeof(char));
	map->lines[map->nline] = map->line;
	if (!map->line)
		memory_error(map);
	map->pline = map->line;
	map->linelen = 0;
	return (true);
}

/* Réalloue un bloc de mémoire 2 fois plus grand si la largeur de la map
 * (inconnue pour le moment et determinée par la longueur de la première ligne
 * après entete) est plus grande que la valeur initiale ou actuelle.
*/
void	realloc_1stline(t_map *map)
{
	const int	newsize = map->width * 2;
	char		*new1stline;

	new1stline = malloc((newsize + 1) * sizeof(char));
	if (!new1stline)
		memory_error(map);
	ft_strncpy(new1stline, map->line, map->linelen);
	free(map->line);
	map->lines[0] = new1stline;
	map->line = new1stline;
	map->pline = new1stline + map->linelen;
	map->width = newsize;
	if (map->cf.dbg_flags & DBG_VERBOSE)
		ft_printf("[realloc_1stline] new size = %i\n", newsize);
}

/* Après lecture de chaque ligne, on valide sa longueur et on termine par '\0'.
 * Toutes les lignes doivent etre de meme longueur (cad: map->witdh qui est
 * fixée par la longueur de la première ligne).
 * Renvoie true (validé) ou false (echec)
 */
bool	validate_line_length(t_map *map)
{
	if (map->nline == 0)
	{
		if (map->linelen < 1)
			return (false);
		map->width = map->linelen;
	}
	if (map->nline > 0 && map->linelen != map->width)
		return (false);
	*map->pline = '\0';
	return (true);
}

/* A chaque lecture d'un caractère, on valide et on l'ajoute à map->pline.
 * Test longueur ligne: réallocation éventuelle si première ligne (sinon echec)
 * Test validité du caractere: car-osbtcale ou car-vide
 * Renvoie true (validé) ou false (échec)
*/
bool	validate_line_char(t_map *map, char c)
{
	if (map->linelen >= map->width)
	{
		if (map->nline > 0)
			return (false);
		realloc_1stline(map);
	}
	if (c != map->chr_empty && c != map->chr_obst)
		return (false);
	*map->pline++ = c;
	map->linelen++;
	return (true);
}

/* Traite le buffer pour remplir les lignes de la map
 * renvoie 0 si ok (on attend la suite), 1 si erreur
 * et 2 si termine (map ok)
 */
int	fill_lines(t_map *map, char *buffer, int bytes_remain)
{
	while (bytes_remain > 0)
	{
		if (*buffer == '\n')
		{
			if (!validate_line_length(map))
				return (FILL_LINES_ERROR);
			if (!alloc_nextline(map))
				return (FILL_LINES_COMPLETED);
		}
		else
			if (!validate_line_char(map, *buffer))
				return (FILL_LINES_ERROR);
		bytes_remain--;
		buffer++;
	}
	return (FILL_LINES_OK);
}
