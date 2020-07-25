/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_functions_unsigned.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraphard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 20:35:04 by sraphard          #+#    #+#             */
/*   Updated: 2020/07/16 17:59:13 by sraphard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_wri_uns_min(t_outp *conv, unsigned int value, int size, int minw)
{
	int		x;
	char	*string;

	string = ft_itoa_uns(value);
	if (conv->prec_width)
	{
		ft_dis_loop('0', conv->prec_width - size, conv);
		if (conv->prec && !conv->prec_width && !value)
			ft_display(" ", minw ? 1 : 0, conv);
		else
			ft_display(string, ft_strlen(string), conv);
	}
	else
	{
		if (conv->prec && !conv->prec_width && !value)
			ft_display(" ", minw ? 1 : 0, conv);
		else
			ft_display(string, ft_strlen(string), conv);
	}
	if (conv->prec_width > size)
		x = conv->min_width - conv->prec_width;
	else
		x = conv->min_width - size;
	ft_dis_loop(' ', x, conv);
	free(string);
}

static void	ft_zero_flag_prec(t_outp *conv, unsigned int value, char *string)
{
	int	x;

	if (conv->prec_width < 0)
	{
		x = ft_abs(conv->min_width) - ft_strlen(string);
		x = ft_dis_loop('0', x, conv);
	}
	else
	{
		if ((int)ft_abs(conv->prec_width) > ft_strlen(string))
			x = ft_abs(conv->min_width) - ft_abs(conv->prec_width);
		else
			x = ft_abs(conv->min_width) - ft_strlen(string);
		ft_dis_loop(' ', x, conv);
		ft_dis_loop('0', ft_abs(conv->prec_width) - ft_strlen(string), conv);
	}
	if (conv->min_width && !conv->prec_width && !value)
		ft_display(" ", 1, conv);
	else if (conv->min_width || conv->prec_width || value)
		ft_display(string, ft_strlen(string), conv);
}

static void	ft_write_uns_zero_flag(t_outp *conv, unsigned int value)
{
	int		x;
	char	*string;

	string = ft_itoa_uns(value);
	if (!conv->prec)
	{
		x = conv->min_width - ft_get_size_unsigned(value);
		ft_dis_loop(conv->prec ? ' ' : '0', x, conv);
		ft_display(string, ft_strlen(string), conv);
	}
	else if (conv->prec)
		ft_zero_flag_prec(conv, value, string);
	free(string);
}

static void	ft_write_uns_noflag(t_outp *conv, unsigned int value)
{
	int		x;
	char	*string;

	string = ft_itoa_uns(value);
	if (conv->prec_width < ft_get_size_unsigned(value))
		x = conv->min_width - ft_get_size_unsigned(value);
	else
		x = conv->min_width - conv->prec_width;
	ft_dis_loop(' ', x, conv);
	x = conv->prec_width - ft_get_size_unsigned(value);
	ft_dis_loop('0', x, conv);
	if (conv->prec && !conv->prec_width && !value)
		ft_display(" ", conv->min_width ? 1 : 0, conv);
	else
		ft_display(string, ft_strlen(string), conv);
	free(string);
}

void		ft_write_unsigned_int(t_outp *conv)
{
	unsigned int	value;
	int				size;

	value = (va_arg(conv->args, unsigned int));
	size = ft_get_size_unsigned(value);
	if (ft_strchr(conv->flags, '-'))
		ft_wri_uns_min(conv, value, size, conv->min_width);
	else if (ft_strchr(conv->flags, '0'))
		ft_write_uns_zero_flag(conv, value);
	else
		ft_write_uns_noflag(conv, value);
}
