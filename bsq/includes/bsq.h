/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/02/25 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <stdbool.h>

# define FILE_BUF_SIZE_KB 16
# define FILE_BUF_MIN_KB 1
# define FILE_BUF_MAX_KB 256
# define MAP_WIDTH_INIT 256
# define ERR_MAP_INVALID "map error"
# define LINE_RET true
# define LINE_NORET false
# define FILL_LINES_OK 0
# define FILL_LINES_ERROR 1
# define FILL_LINES_COMPLETED 2
# define DBG_VERBOSE 1
# define DBG_MATRIX  2
# define DBG_PRN_SPC  4
# define DBG_PRN_MAP0 8
# define DBG_PRN_RAWSOL 16

typedef unsigned int	t_uint;
typedef unsigned short	t_word;
typedef unsigned char	t_byte;
typedef t_word			t_mtxn;

typedef struct s_bsqconf
{
	int	dbg_flags;
	int	file_buffer_size;
}	t_bsqconf;

typedef struct s_option
{
	char	*name;
	int		(*action)(int argc, char **argv, t_bsqconf *conf);
}	t_option;

typedef struct s_map
{
	t_mtxn		*matrix;
	char		*filebuffer;
	int			nline;
	char		**lines;
	int			nblines;
	int			width;
	char		chr_empty;
	char		chr_obst;
	char		chr_fill;
	int			sol_size;
	int			sol_line0;
	int			sol_line1;
	int			sol_x0;
	int			sol_x1;
	char		*line;
	char		*pline;
	int			linelen;
	t_bsqconf	cf;
}	t_map;

void	print_help_and_exit(void);
int		parse_opt(int argc, char **argv, t_bsqconf *conf);
void	test_hard_map(t_bsqconf cf);
void	fill_map(t_map *map);
void	clean_map(t_map *map);
void	print_map(t_map *map);
void	print_matrix(t_map *map);
void	print_sol_coord(t_map *map);
void	print_solution(t_map *map);
t_map	*load_map(char *filename, t_bsqconf cf);
bool	read_map(t_map *map, int fdesc);
bool	alloc_nextline(t_map *map);
int		fill_lines(t_map *map, char *buffer, int bytes_remain);
void	find_solution_bt(t_map *map, int line0, int xstart, int xend);
int		find_solution(t_map *map);
void	ft_free(void **ptr);
void	free_map(t_map **map);
void	memory_error(t_map *map);

#endif
