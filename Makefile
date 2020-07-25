# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sraphard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/28 14:42:06 by sraphard          #+#    #+#              #
#    Updated: 2020/07/13 18:54:06 by sraphard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_parse_functions.c ft_write_functions_hex.c ft_write_functions_num.c ft_write_functions_unsigned.c ft_write_function_char.c ft_write_percent.c ft_printf_utils.c ft_printf.c libft/ft_atoi.c libft/ft_isdigit.c libft/ft_memcpy.c libft/ft_putstr_fd.c libft/ft_strlcpy.c libft/ft_strtrim.c libft/ft_bzero.c libft/ft_isprint.c libft/ft_memmove.c libft/ft_split.c libft/ft_strlen.c libft/ft_substr.c libft/ft_calloc.c libft/ft_itoa.c libft/ft_itoa_uns.c libft/ft_memset.c libft/ft_strchr.c libft/ft_strmapi.c libft/ft_tolower.c libft/ft_isalnum.c libft/ft_memccpy.c libft/ft_putchar_fd.c libft/ft_strdup.c libft/ft_strncmp.c libft/ft_toupper.c libft/ft_isalpha.c libft/ft_memchr.c libft/ft_putendl_fd.c libft/ft_strjoin.c libft/ft_strnstr.c libft/ft_isascii.c libft/ft_memcmp.c libft/ft_putnbr_fd.c libft/ft_strlcat.c libft/ft_strrchr.c libft/ft_get_size_number.c libft/ft_revert_array.c libft/ft_dec_to_binary_convert.c libft/ft_strcmp.c libft/ft_dec_to_binary_32bits_convert.c libft/ft_binary_to_hex_convert.c libft/ft_dec_to_hex_convert.c libft/ft_power.c libft/ft_put_unsigned_fd.c libft/ft_abs.c libft/ft_get_size_unsigned.c libft/ft_strncat.c libft/ft_delchar.c libft/ft_strcat.c libft/ft_strnjoin.c libft/ft_strrep.c

OBJS		=	${SRCS:.c=.o}

FLAGS		=	-Wall -Wextra -Werror -g

NAME		=	libftprintf.a

RM			=	rm -rf

all			:	${NAME}

$(NAME)		:	${OBJS}
				ar rcs ${NAME} ${OBJS}
				ranlib ${NAME}

.c.o		:
				gcc ${FLAGS} -c $< -o ${<:.c=.o}

clean		:
				${RM} ${OBJS}

fclean		:	clean
				${RM} ${NAME}

re			:	fclean all

allc		:	all clean
				make -C libft/ clean

rec			:	re clean
