/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_digit(char c)
{
	int	digit;

	digit = -1;
	if (c >= '0' && c <= '9')
		digit = c - '0';
	if (c >= 'a' && c <= 'z')
		digit = c - 'a' + 10;
	if (c >= 'A' && c <= 'Z')
		digit = c - 'A' + 10;
	return (digit);
}

int	str2int(const char *str, int base, char **pend)
{
	int	num;
	int	signe;
	int	digit;

	num = 0;
	signe = 1;
	while (*str == '+' || *str == '-'
		|| *str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
	{
		if (*str == '-')
			signe = -signe;
		str++;
	}
	digit = get_digit(*str);
	while (digit >= 0 && digit < base)
	{
		num = base * num + digit;
		digit = get_digit(*++str);
	}
	if (pend)
		*pend = (char *)str;
	return (num * signe);
}

int	ft_atoi(char *str)
{
	return (str2int(str, 10, 0));
}

/* Ecrit dans <buf> la representation en base <base> de <nbr>.
 * Attention : n'ajoute PAS de caratere terminal '\0' à la fin.
 * Renvoie un pointeur sur le caratere suivant le dernier chiffre.
*/
char	*int2str(int nbr, unsigned int base, char *buf)
{
	unsigned int	unbr;
	char			c;

	unbr = nbr;
	if (nbr < 0)
	{
		*buf++ = '-';
		unbr = -nbr;
	}
	if (unbr >= base)
		buf = int2str(unbr / base, base, buf);
	unbr %= base;
	if (unbr < 10)
		c = '0' + unbr;
	else
		c = 'a' + unbr - 10;
	*buf++ = c;
	return (buf);
}

char	*ft_itoa(int nbr, int base, char *buf)
{
	*int2str(nbr, base, buf) = '\0';
	return (buf);
}

/*#include <stdio.h>

void test_strnum_c()
{
	char buffer[34], buffer2[34];
	const char *snum = "7aFceBDd";
	
	printf(">>> Tests des fonctions ft_itoa et str2int (fichier strnum.c)\n");
	printf(" 0 =  %s$\n", ft_itoa(0, 10, buffer));
	printf("-1 = %s$\n", ft_itoa(-1, 10, buffer));
	printf("max int =  %s$\n", ft_itoa(0x7fffffff, 10, buffer));
	printf("min int = %s$\n", ft_itoa((int)0x80000000, 10, buffer));
	printf("1234567890 = [hexa] %s$\n", ft_itoa(1234567890, 16, buffer));
	printf("retour en base 10 : %s$\n",
		ft_itoa(str2int(buffer, 16, 0), 10, buffer));
	printf("%s : base10: %s  base16: %s\n", snum,
		ft_itoa(str2int(snum, 16, 0), 10, buffer),
		ft_itoa(str2int(snum, 16, 0), 16, buffer2));
}
*/