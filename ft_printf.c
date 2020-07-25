/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraphard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:46:07 by sraphard          #+#    #+#             */
/*   Updated: 2020/07/18 16:05:37 by sraphard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_loop(char *s, t_outp *conv)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '%' && s[i + 1] == '%')
			ft_display(s + ++i, 1, conv);
		else if (s[i] == '%' && s[i + 1])
		{
			ft_struct_initialize(conv);
			ft_fill(conv, s, &i);
			ft_write_conversion(conv, s, i);
		}
		else
			ft_display(s + i, 1, conv);
}

int			ft_printf(const char *s, ...)
{
	t_outp	conv;

	va_start(conv.args, s);
	conv.length = 0;
	ft_printf_loop((char *)s, &conv);
	va_end(conv.args);
	return (conv.length);
}
