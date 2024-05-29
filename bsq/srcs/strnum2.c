/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnum2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int nbr)
{
	unsigned int	unbr;
	char			d;

	unbr = nbr;
	if (nbr < 0)
	{
		write(1, "-", 1);
		unbr = -nbr;
	}
	if (unbr < 10)
	{
		d = unbr + '0';
		write(1, &d, 1);
	}
	else
	{
		ft_putnbr(unbr / 10);
		ft_putnbr(unbr % 10);
	}
}

/* Ecrit dans <buf> la representation en base <base> de <nbr>.
 * Attention : n'ajoute PAS de caratere terminal '\0' à la fin.
 * Renvoie un pointeur sur le caratere suivant le dernier chiffre.
*/
char	*long2str(long nbr, unsigned int base, char *buf)
{
	unsigned long	unbr;
	char			c;

	unbr = nbr;
	if (nbr < 0)
	{
		*buf++ = '-';
		unbr = -nbr;
	}
	if (unbr >= base)
		buf = long2str(unbr / base, base, buf);
	unbr %= base;
	if (unbr < 10)
		c = '0' + unbr;
	else
		c = 'a' + unbr - 10;
	*buf++ = c;
	return (buf);
}

char	*ft_ltoa(long nbr, int base, char *buf)
{
	*long2str(nbr, base, buf) = '\0';
	return (buf);
}
