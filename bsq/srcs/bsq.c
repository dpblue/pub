/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr & hucherea                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:39:12 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/02/25 20:39:15 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allowed C functions: exit, open, close, write, read, malloc, free */

#include <stdlib.h>
#include <stddef.h>
#include "bsq.h"
#include "ft_str_nbr.h"

void	print_help_and_exit(void)
{
	ft_printf("-------------------------------------------------\n");
	ft_printf(" BSQ piscine 42 - feb. 2024\n");
	ft_printf("  -> Aurelien (ade-sarr) & Hugo (hucherea)\n");
	ft_printf("-------------------------------------------------\n");
	ft_printf(" + file reading buffer size: from 4 KB to 64 KB\n");
	ft_printf(" + smart memory (re)allocation for map first line\n");
	ft_printf(" + fast solve algorithm !\n");
	ft_printf("-------------------------------------------------\n");
	ft_printf("option: --debug <sum_of_flags>\n");
	ft_printf("option: --debug 1  : verbose mode\n");
	ft_printf("option: --debug 2  : print solution matrix\n");
	ft_printf("option: --debug 4  : print map with correct square ratio\n");
	ft_printf("option: --debug 8  : print loaded map\n");
	ft_printf("option: --debug 16 : print square coord. instead of sol. map\n");
	ft_printf("option: --bufsize <size in KiB>");
	exit(0);
}

bool	process_map(char *filename, t_bsqconf conf)
{
	t_map	*map;

	map = load_map(filename, conf);
	if (!map)
	{
		ft_puterrmsg(ERR_MAP_INVALID);
		return (false);
	}
	if (conf.dbg_flags & DBG_PRN_MAP0)
	{
		print_map(map);
		ft_putchar('\n');
	}
	find_solution(map);
	print_solution(map);
	free_map(&map);
	return (true);
}

/* Traite les fichiers passés en ligne de commande via appel à process_map()
 * Si aucun fichier trouvé alors on lit sur l'entrée standard tant qu'elle
 * fournit des map valides.
*/
void	process_files(int nb_args, char **names, t_bsqconf conf)
{
	int	i;
	int	nb_files;

	i = 0;
	nb_files = 0;
	while (i < nb_args)
	{
		if (names[i] && *names[i])
		{
			if (nb_files > 0)
				ft_putchar('\n');
			process_map(names[i], conf);
			nb_files++;
		}
		i++;
	}
	if (nb_files == 0)
		while (process_map(NULL, conf))
			;
}

/* Traite les options et renseigne la struct <conf>
 * Au retour, les arguments de la ligne de commande qui ont été reconnus
 * comme des options sont neutralisés : mis à longueur nulle.
*/
void	parse_options(int argc, char **argv, t_bsqconf *conf)
{
	int	i;

	i = 0;
	while (i < argc)
		i += parse_opt(argc - i, argv + i, conf);
}

int	main(int argc, char **argv)
{
	t_bsqconf	config;

	config.dbg_flags = 0;
	config.file_buffer_size = FILE_BUF_SIZE_KB * 1024;
	parse_options(argc - 1, argv + 1, &config);
	process_files(argc - 1, argv + 1, config);
	return (0);
}
