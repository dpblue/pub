/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:17:23 by hucherea          #+#    #+#             */
/*   Updated: 2024/05/29 02:25:30 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include "ft_str_nbr.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

/* Lis le fichier (texte) <fdesc> jusqu'au prochain caractere <LF>
 * (ou jusqu'a <size> car.) et remplit de le buffer avec les char lus.
 * Renvoie le nombre de car. lus ou -1 si erreur de lecture sur read().
*/
int	read_line(int fdesc, char *buffer, int size)
{
	int	bytes_read;
	int	nb_read;

	bytes_read = 0;
	while (bytes_read < size)
	{
		nb_read = read(fdesc, buffer, 1);
		if (nb_read < 0)
			return (-1);
		if (nb_read == 0)
			return (bytes_read);
		if (*buffer == '\n')
			return (bytes_read + 1);
		bytes_read++;
		buffer++;
	}
	return (bytes_read);
}

bool	validate_chars(t_map *map, char emp, char obs, char fil)
{
	const bool	valid = emp != obs && emp != fil && obs != fil
		&& emp >= 32 && emp <= 126
		&& obs >= 32 && obs <= 126
		&& fil >= 32 && fil <= 126;

	if (valid)
	{
		map->chr_empty = emp;
		map->chr_obst = obs;
		map->chr_fill = fil;
	}
	return (valid);
}

/* Initialise la map en lisant l'entete du fichier (la premiere ligne).
 * renseigne map->nblines et les valeurs des caracteres empty/obst/fill
 * Renvoie true ou false si entete valide ou non.
*/
bool	init_map(t_map *map, int fdesc)
{
	static char	*status[2] = {"error", "ok"};
	char		buffer[80];
	char		*pbuf;
	bool		is_valid;
	int			read;

	is_valid = false;
	read = read_line(fdesc, buffer, 80);
	if (read >= 5)
	{
		pbuf = buffer + read - 4;
		if (validate_chars(map, pbuf[0], pbuf[1], pbuf[2]))
		{
			*pbuf = 0;
			map->nblines = ft_atoi(buffer);
			is_valid = map->nblines > 0;
		}
	}
	if (map->cf.dbg_flags & DBG_VERBOSE)
		ft_printf("[init_map: %s] nblines: %i  "
			"empty:'%c' obst:'%c' fill:'%c'\n", status[is_valid],
			map->nblines, map->chr_empty, map->chr_obst, map->chr_fill);
	return (is_valid);
}

t_map	*new_map(t_bsqconf conf)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		memory_error(NULL);
	map->cf = conf;
	map->lines = NULL;
	map->matrix = NULL;
	map->filebuffer = NULL;
	return (map);
}

/* Crée et renvoie une structure map valide à partir d'un fichier map
 * Renvoie NULL si le fichier est non valide (ou ne peut etre ouvert).
*/
t_map	*load_map(char *filename, t_bsqconf conf)
{
	t_map	*map;
	int		fdesc;
	bool	is_valid;

	fdesc = 0;
	if (filename)
		fdesc = open(filename, O_RDONLY);
	if (fdesc == -1)
		return (NULL);
	map = new_map(conf);
	is_valid = false;
	if (init_map(map, fdesc))
		is_valid = read_map(map, fdesc);
	ft_free((void **)&map->filebuffer);
	if (!is_valid)
		free_map(&map);
	else if (conf.dbg_flags & DBG_VERBOSE)
		ft_printf("Map <%s> loaded : %i x %i\n",
			filename, map->width, map->nblines);
	if (fdesc)
		close(fdesc);
	return (map);
}
