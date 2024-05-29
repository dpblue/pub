/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_nbr.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STR_NBR_H
# define FT_STR_NBR_H

# include <stdbool.h>

typedef unsigned int	t_uint;

void	ft_putchar(char c);
void	ft_putstr(char *str, bool lineret);
void	ft_puterrmsg(char *str);
void	print(char *str);
void	ft_printf(char *format, ...);
void	ft_putnbr(int nbr);
int		ft_atoi(char *str);
int		str2int(const char *str, int base, char **pend);
char	*ft_itoa(int nbr, int base, char *buf);
char	*ft_ltoa(long nbr, int base, char *buf);
int		ft_strlen(const char *str);
t_uint	ft_strlcpy(char *dest, char *src, unsigned int size);
char	*ft_strncpy(char *dest, const char *src, unsigned int n);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, unsigned int n);

#endif