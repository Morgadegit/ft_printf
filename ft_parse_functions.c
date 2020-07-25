/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraphard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:27:13 by sraphard          #+#    #+#             */
/*   Updated: 2020/07/18 16:07:35 by sraphard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_get_caps(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] >= 97 && s[i] <= 122)
			s[i] -= 32;
	return (s);
}

static int	ft_get_min_width(t_outp *conv, char *s, int *i, int *minwdone)
{
	int	width;

	*minwdone = 1;
	width = ft_atoi(s + *i);
	(*i) += ft_get_size_number(width) - 1;
	if (conv->star == 1 || conv->star == 3)
	{
		if (width)
			conv->error = -1;
		width = va_arg(conv->args, int);
		return (width);
	}
	else
		return (width);
}

static int	ft_get_prec_width(t_outp *conv, char *s, int *i)
{
	int	width;

	conv->prec = 1;
	width = ft_atoi(s + *i + 1);
	(*i) += ft_get_size_number(width);
	if (conv->star == 2 || conv->star == 3)
	{
		if (width)
			conv->error = -1;
		return (width = va_arg(conv->args, int));
	}
	else
		return (width);
}

static void	ft_fill_loop(t_outp *conv, char *s, int *i, int j)
{
	int	minwdone;

	minwdone = 0;
	while (s[(*i)] && !conv->conversion)
	{
		if ((s[*i] == '-' || s[*i] == '0') && !conv->min_width && !conv->prec)
			conv->flags = ft_strnjoin(conv->flags, s + (*i), 1);
		else if (!minwdone && ((s[*i] >= '1' && s[*i] <= '9') ||
				(conv->star == 1 || conv->star == 3)))
			conv->min_width = ft_get_min_width(conv, s, i, &minwdone);
		else if (s[*i] == '*' && !conv->prec)
			conv->star = 1;
		else if (s[*i] == '.')
		{
			minwdone = 1;
			if (s[*i + 1] == '*')
				conv->star = conv->star == 1 ? 3 : 2;
			conv->prec_width = ft_get_prec_width(conv, s, i);
		}
		else if (ft_strrchr("cdisupxX", s[*i]) || (s[*i] == '%' && *i != j))
			conv->conversion = s[*i];
		(*i)++;
	}
}

void		ft_fill(t_outp *conv, char *s, int *i)
{
	ft_fill_loop(conv, s, i, *i);
	if (!conv->conversion)
		(*i)--;
	(*i)--;
	if (conv->min_width < 0)
	{
		conv->flags = ft_strnjoin(conv->flags, "-", 1);
		conv->min_width *= -1;
	}
}
