/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_functions_hexa.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraphard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:05:01 by sraphard          #+#    #+#             */
/*   Updated: 2020/07/16 18:45:12 by sraphard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_write_hex_minus_flag(t_outp *conv, int size, char *value)
{
	int	x;

	x = 0;
	if (conv->prec)
	{
		if (ft_strcmp(value, "0") && !conv->prec_width)
			ft_strrep(&value, "");
		ft_dis_loop('0', conv->prec_width - size, conv);
	}
	ft_display(value, ft_strlen(value), conv);
	if (conv->prec_width < conv->min_width)
	{
		if (conv->prec_width > (int)ft_strlen(value))
			x = conv->min_width - conv->prec_width;
		else
			x = conv->min_width - (int)ft_strlen(value);
		ft_dis_loop(' ', x, conv);
	}
	if (conv->min_width < 0)
		ft_dis_loop('0', -(conv->min_width) - conv->prec_width, conv);
	free(value);
}

static void	ft_zero_write_hex_norm_prec(t_outp *conv, int size, char *value)
{
	int	x;

	if (conv->prec_width > conv->min_width)
		ft_dis_loop('0', conv->prec_width - size, conv);
	else
	{
		if (size > conv->prec_width)
			x = conv->min_width - size;
		else
			x = conv->min_width - conv->prec_width;
		ft_strcmp(value, "0") && !conv->prec_width ? x++ : 0;
		ft_dis_loop(conv->prec_width < 0 ? '0' : ' ', x, conv);
		ft_dis_loop('0', conv->prec_width - size, conv);
	}
	if (!(ft_strcmp(value, "0") && !conv->prec_width))
		ft_display(value, ft_strlen(value), conv);
}

static void	ft_write_hex_zero_flag(t_outp *conv, int size, char *value)
{
	if (conv->prec)
		ft_zero_write_hex_norm_prec(conv, size, value);
	else
	{
		ft_dis_loop('0', conv->min_width - size, conv);
		ft_display(value, ft_strlen(value), conv);
	}
	free(value);
}

static void	ft_write_hex_noflag(t_outp *conv, int size, char *value)
{
	int	x;

	if (conv->prec)
	{
		if (ft_strcmp(value, "0") && !conv->prec_width)
			ft_strrep(&value, conv->min_width ? " " : "");
		if (conv->prec_width < size)
			x = conv->min_width - size;
		else
			x = conv->min_width - conv->prec_width;
		ft_dis_loop(' ', x, conv);
		ft_dis_loop('0', conv->prec_width - size, conv);
	}
	else
		ft_dis_loop(' ', conv->min_width - ft_strlen(value), conv);
	ft_display(value, ft_strlen(value), conv);
	free(value);
}

void		ft_write_hex(t_outp *conv)
{
	char	*value;

	if (conv->conversion == 'p')
	{
		if (!(value = ft_d_t_h_conv_p(va_arg(conv->args, unsigned long long))))
			value = ft_strdup("(nil)");
		else
		{
			while (ft_strlen(value) < conv->prec_width)
				value = ft_strjoin("0", value, 1);
			value = ft_strjoin("0x", value, 1);
		}
	}
	else if (conv->conversion == 'X')
		value = ft_get_caps(ft_dec_to_hex_convert(va_arg(conv->args, int)));
	else
		value = ft_dec_to_hex_convert(va_arg(conv->args, int));
	if (ft_strchr(conv->flags, '-'))
		ft_write_hex_minus_flag(conv, ft_strlen(value), value);
	else if (ft_strchr(conv->flags, '0'))
		ft_write_hex_zero_flag(conv, ft_strlen(value), value);
	else
		ft_write_hex_noflag(conv, ft_strlen(value), value);
}
