/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include "ft_str_nbr.h"

void	check_next_arg(int argc, char **argv)
{
	if (argc < 2 || ft_strncmp(argv[1], "--", 2) == 0)
		print_help_and_exit();
}

int	skip_optargs_x2(char **argv)
{
	*argv[0] = '\0';
	*argv[1] = '\0';
	return (2);
}

int	fn_opt_debug(int argc, char **argv, t_bsqconf *conf)
{
	check_next_arg(argc, argv);
	conf->dbg_flags = ft_atoi(argv[1]);
	return (skip_optargs_x2(argv));
}

int	fn_opt_bufsize(int argc, char **argv, t_bsqconf *conf)
{
	int	bufsize_kib;

	check_next_arg(argc, argv);
	bufsize_kib = ft_atoi(argv[1]);
	if (bufsize_kib >= FILE_BUF_MIN_KB && bufsize_kib <= FILE_BUF_MAX_KB)
		conf->file_buffer_size = bufsize_kib * 1024;
	else
		conf->file_buffer_size = FILE_BUF_SIZE_KB * 1024;
	return (skip_optargs_x2(argv));
}

int	parse_opt(int argc, char **argv, t_bsqconf *conf)
{
	static const t_option	options[] = {
	{"--debug", fn_opt_debug},
	{"--bufsize", fn_opt_bufsize}};
	static const int		nb_options = sizeof(options) / sizeof(*options);
	int						i;

	i = 0;
	while (i < nb_options)
	{
		if (ft_strcmp(*argv, options[i].name) == 0)
			return (options[i].action(argc, argv, conf));
		i++;
	}
	if (ft_strncmp(*argv, "--", 2) == 0)
		print_help_and_exit();
	return (1);
}
