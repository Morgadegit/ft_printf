/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraphard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 19:34:24 by sraphard          #+#    #+#             */
/*   Updated: 2020/07/18 16:08:32 by sraphard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_write_per(t_outp *conv, char *s, int i)
{
	int	j;
	int	k;

	j = 0;
	k = i;
	i--;
	while (s[i] != '%')
		i--;
	j = i;
	i++;
	while (!ft_isalpha(s[i]) && s[i] != '%' && s[i])
		i++;
	if (s[i] == '%')
		ft_display("%", 1, conv);
	else
		ft_display(s + j, k - j + 1, conv);
}
