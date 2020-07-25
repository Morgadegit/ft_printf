/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraphard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:04:47 by sraphard          #+#    #+#             */
/*   Updated: 2020/07/18 16:05:56 by sraphard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

typedef struct	s_outp
{
	char	*flags;
	int		star;
	char	sep;
	int		min_width;
	int		prec;
	int		prec_width;
	char	conversion;
	int		error;
	int		length;
	va_list	args;
}				t_outp;
int				ft_printf(const char *s, ...);
int				ft_dis_loop(char c, int nb, t_outp *conv);
int				ft_display(char *s, int nb, t_outp *conv);
int				ft_display_gate(char *s, int nb, t_outp *conv);
void			ft_fill(t_outp *conv, char *s, int *i);
void			ft_write_conversion(t_outp *conv, char *s, int i);
void			ft_write_hex(t_outp *conv);
void			ft_write_unsigned_int(t_outp *conv);
void			ft_write_char(t_outp *conv);
void			ft_write_string(t_outp *conv);
void			ft_write_int(t_outp *conv);
void			ft_write_per(t_outp *conv, char *s, int i);
void			ft_struct_initialize(t_outp *conv);
char			*ft_get_caps(char *s);

#endif
