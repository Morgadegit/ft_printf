/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraphard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 19:34:34 by sraphard          #+#    #+#             */
/*   Updated: 2020/07/18 16:08:19 by sraphard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_struct_initialize(t_outp *conv)
{
	conv->flags = ft_strdup("");
	conv->star = 0;
	conv->sep = 0;
	conv->min_width = 0;
	conv->prec = 0;
	conv->prec_width = 0;
	conv->conversion = 0;
	conv->error = 0;
}

void	ft_write_conversion(t_outp *conv, char *s, int i)
{
	if (conv->conversion == 'c')
		ft_write_char(conv);
	else if (conv->conversion == 's')
		ft_write_string(conv);
	else if (conv->conversion == 'd' || conv->conversion == 'i')
		ft_write_int(conv);
	else if (conv->conversion == 'u')
		ft_write_unsigned_int(conv);
	else if (conv->conversion == 'x' ||
		conv->conversion == 'X' || conv->conversion == 'p')
		ft_write_hex(conv);
	else if (ft_strchr("%w", conv->conversion))
		ft_write_per(conv, s, i);
	free(conv->flags);
}

int		ft_dis_loop(char c, int nb, t_outp *conv)
{
	int r;

	r = nb;
	if (nb > 0)
		conv->length += nb;
	while (nb-- > 0)
		ft_putchar_fd(c, 1);
	return (r > 0 ? r : 0);
}

int		ft_display_gate(char *s, int nb, t_outp *conv)
{
	int	i;

	i = 0;
	if (ft_strlen(s) < nb)
		nb = ft_strlen(s);
	conv->length += nb;
	while (nb-- > 0)
		ft_putchar_fd(s[i++], 1);
	return (i > 0 ? i : 0);
}

int		ft_display(char *s, int nb, t_outp *conv)
{
	int	i;

	i = 0;
	if (ft_strlen(s) > nb)
		conv->length += nb;
	else
		conv->length += ft_strlen(s);
	while (nb-- > 0)
		ft_putchar_fd(s[i++], 1);
	return (i > 0 ? i : 0);
}
