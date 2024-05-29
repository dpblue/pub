/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "ft_str_nbr.h"

void	print(char *str)
{
	write(1, str, ft_strlen(str));
}

void	print_arg(char *format, va_list *args, char *sbuf)
{
	if (*format == 's')
		print(va_arg(*args, char *));
	if (*format == 'c')
		ft_putchar(va_arg(*args, int));
	if (*format == 'd' || *format == 'i')
		print(ft_itoa(va_arg(*args, int), 10, sbuf));
	if (*format == 'b')
		print(ft_itoa(va_arg(*args, int), 2, sbuf));
	if (*format == 'h')
		print(ft_itoa(va_arg(*args, int), 16, sbuf));
	if (*format == 'p')
		print(ft_ltoa(va_arg(*args, long), 16, sbuf));
	if (*format == '%')
		write(1, "%", 1);
}

/*
 * ft_printf opere dans le meme esprit que printf: dans la chaine <format>,
 * les caracteres spéciaux qui suivent un '%' signifient qu'il faut inserer
 * la valeur de l'argument respectif de la liste des arguments qui suivent.
 *    's' : string (char *)
 *    'c' : char
 *    'd' ou 'i' : decimal (int)
 *    'b' : binaire (int)
 *    'h' : hexadecimal (int)
 *    'p' : pointeur (long) affiché en hexa
*/
void	ft_printf(char *format, ...)
{
	va_list	args;
	char	sbuf[34];
	char	*form0;
	bool	new_arg;

	va_start(args, format);
	while (*format)
	{
		form0 = format;
		while (*format && *format != '%')
			format++;
		new_arg = (*format == '%');
		if (format > form0)
			write(1, form0, format - form0);
		if (new_arg)
		{
			print_arg(++format, &args, sbuf);
			if (*format)
				format++;
		}
	}
	va_end(args);
}

void	test_ft_printf(void)
{
	const int	i = 0xAF;
	const char	*h = "Hello!";

	ft_printf(">>> Test de la fonction ft_printf\n");
	ft_printf("%i%d=%s\n", 4, 2, "42");
	ft_printf("%i%d=%s\n", 42, 24, "4224");
	ft_printf("nombre %i : base 2: %b  base 10: %d  base 16: %h\n", i, i, i, i);
	ft_printf("%c%c%c%c%c%c\n", 'H', 'e', 'l', 'l', 'o', '!');
	ft_printf("%c%c%c%c%c%c\n", h[0], h[1], h[2], h[3], h[4], h[5]);
	ft_printf("pointeur : [%p]\n", &i);
}
