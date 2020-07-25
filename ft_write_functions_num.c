/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_functions_num.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraphard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:46:59 by sraphard          #+#    #+#             */
/*   Updated: 2020/07/16 17:56:59 by sraphard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_write_int_minus_flag(t_outp *conv, int value)
{
	int		x;
	char	*string;

	string = ft_itoa_uns(ft_abs(value));
	if (conv->prec)
	{
		ft_display("-", value < 0 ? 1 : 0, conv);
		ft_dis_loop('0', conv->prec_width - ft_strlen(string), conv);
		if (conv->prec_width || value)
			ft_display(string, ft_strlen(string), conv);
	}
	else
	{
		ft_display("-", value < 0 ? 1 : 0, conv);
		ft_display(string, ft_strlen(string), conv);
	}
	if ((conv->prec && !conv->prec_width && !value) ||
			(conv->prec_width > ft_strlen(string)))
		x = conv->min_width - conv->prec_width;
	else
		x = conv->min_width - ft_strlen(string);
	ft_dis_loop(' ', value < 0 ? x - 1 : x, conv);
	free(string);
}

static void	ft_anti_norm_zero_flag_prec(t_outp *conv, char *string, int value)
{
	int	x;

	if (conv->prec_width < 0)
	{
		x = conv->min_width - ft_strlen(string);
		value < 0 ? x-- : 0;
		ft_display("-", value < 0 ? 1 : 0, conv);
		ft_dis_loop('0', x, conv);
	}
	else
	{
		if ((int)ft_abs(conv->prec_width) > ft_strlen(string))
			x = ft_abs(conv->min_width) - ft_abs(conv->prec_width);
		else
			x = ft_abs(conv->min_width) - ft_strlen(string);
		ft_dis_loop(' ', value < 0 ? x - 1 : x, conv);
		ft_display("-", value < 0 ? 1 : 0, conv);
		x = value < 0 ? 1 : 0;
		ft_dis_loop('0', ft_abs(conv->prec_width) - ft_strlen(string), conv);
	}
	if (conv->min_width && !conv->prec_width && !value)
		ft_display(" ", 1, conv);
	else if (conv->min_width || conv->prec_width || value)
		ft_display(string, ft_strlen(string), conv);
}

static void	ft_write_int_zero_flag(t_outp *conv, int value)
{
	int		x;
	char	*string;

	string = ft_itoa_uns(ft_abs(value));
	if (!conv->prec)
	{
		x = conv->min_width - ft_strlen(string);
		ft_display("-", value < 0 ? 1 : 0, conv);
		ft_dis_loop('0', value < 0 ? x - 1 : x, conv);
		ft_display(string, ft_strlen(string), conv);
	}
	else if (conv->prec)
		ft_anti_norm_zero_flag_prec(conv, string, value);
	free(string);
}

static void	ft_write_int_noflag(t_outp *conv, int value)
{
	int		x;
	char	*string;

	string = ft_itoa_uns(ft_abs(value));
	if (conv->prec_width > ft_strlen(string))
		x = conv->min_width - conv->prec_width;
	else
		x = conv->min_width - ft_strlen(string);
	ft_dis_loop(' ', value < 0 ? x - 1 : x, conv);
	x = conv->prec_width - ft_strlen(string);
	ft_display("-", value < 0 ? 1 : 0, conv);
	ft_dis_loop('0', x, conv);
	if (!(conv->prec && !conv->prec_width && !value))
		ft_display(string, ft_strlen(string), conv);
	else if (conv->min_width > 0)
		ft_display(" ", 1, conv);
	free(string);
}

void		ft_write_int(t_outp *conv)
{
	int	value;

	value = va_arg(conv->args, int);
	if (ft_strchr(conv->flags, '-'))
		ft_write_int_minus_flag(conv, value);
	else if (ft_strchr(conv->flags, '0'))
		ft_write_int_zero_flag(conv, value);
	else
		ft_write_int_noflag(conv, value);
}
