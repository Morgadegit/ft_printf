/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_function_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraphard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:12:26 by sraphard          #+#    #+#             */
/*   Updated: 2020/07/16 18:45:14 by sraphard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_write_string_prec_neg(t_outp *conv, char *value)
{
	int x;

	x = 0;
	if (!(ft_strchr(conv->flags, '-')))
		x += ft_dis_loop(' ', ft_abs(conv->min_width) - ft_strlen(value), conv);
	x += ft_display(value, ft_strlen(value), conv);
	return (x);
}

int		ft_write_string_prec_pos(t_outp *conv, char *value)
{
	int x;

	x = 0;
	if ((!ft_strchr(conv->flags, '-') &&
			(int)ft_abs(conv->min_width) < conv->prec_width) ||
		(!ft_strchr(conv->flags, '-') && ft_strlen(value) < conv->prec_width))
		x += ft_dis_loop(' ', ft_abs(conv->min_width) - ft_strlen(value), conv);
	else if (!ft_strchr(conv->flags, '-'))
		x += ft_dis_loop(' ', ft_abs(conv->min_width) - conv->prec_width, conv);
	x += ft_display_gate(value, conv->prec_width, conv);
	return (x);
}

void	ft_write_string(t_outp *conv)
{
	char	*value;
	int		x;

	x = 0;
	if (!(value = ft_strdup(va_arg(conv->args, char *))))
	{
		if  (conv->prec && conv->prec_width > 0 && ft_abs(conv->prec_width) < 6)
			value = ft_strdup("");
		else
			value = ft_strdup("(null)");
	}
	if (conv->prec && conv->prec_width >= 0)
		x += ft_write_string_prec_pos(conv, value);
	else if (conv->prec && conv->prec_width < 0)
		x += ft_write_string_prec_neg(conv, value);
	else
	{
		if (!ft_strchr(conv->flags, '-'))
			x += ft_dis_loop(' ', conv->min_width - ft_strlen(value), conv);
		x += ft_display(value, ft_strlen(value), conv);
	}
	if (ft_strchr(conv->flags, '-'))
		ft_dis_loop(' ', ft_abs(conv->min_width) - x, conv);
	free(value);
}

void	ft_write_char(t_outp *conv)
{
	char	value;

	value = va_arg(conv->args, int);
	if (ft_strchr(conv->flags, '-'))
	{
		ft_dis_loop(value, 1, conv);
		ft_dis_loop(' ', conv->min_width - 1, conv);
	}
	else
	{
		ft_dis_loop(' ', conv->min_width - 1, conv);
		ft_dis_loop(value, 1, conv);
	}
}
