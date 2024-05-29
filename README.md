/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr & hucherea                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 02:42:42 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/25 02:42:42 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allowed C functions: exit, open, close, write, read, malloc, free */

void	print_help(void)
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
}
