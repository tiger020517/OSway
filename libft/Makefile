# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junhykim <junhykim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 10:20:06 by junhykim          #+#    #+#              #
#    Updated: 2024/10/20 09:07:20 by junhykim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					= libft.a

SRCS					= ft_atoi.c \
						ft_bzero.c \
						ft_calloc.c \
						ft_isalnum.c \
						ft_isalpha.c \
						ft_isascii.c \
						ft_isdigit.c \
						ft_isprint.c \
						ft_itoa.c \
						ft_memchr.c \
						ft_memcmp.c \
						ft_memcpy.c \
						ft_memmove.c \
						ft_memset.c \
						ft_putchar_fd.c \
						ft_putendl_fd.c \
						ft_putnbr_fd.c \
						ft_putstr_fd.c \
						ft_split.c \
						ft_strchr.c \
						ft_strdup.c \
						ft_striteri.c \
						ft_strjoin.c \
						ft_strlcat.c \
						ft_strlcpy.c \
						ft_strlen.c \
						ft_strmapi.c \
						ft_strncmp.c \
						ft_strnstr.c \
						ft_strrchr.c \
						ft_strtrim.c \
						ft_substr.c \
						ft_tolower.c \
						ft_toupper.c \
						ft_lstadd_back.c \
						ft_lstadd_front.c \
						ft_lstclear.c \
						ft_lstdelone.c \
						ft_lstiter.c \
						ft_lstlast.c \
						ft_lstmap.c \
						ft_lstnew.c \
						ft_lstsize.c \
						ft_printf.c \
						get_next_line_utils.c \
						get_next_line.c

OBJS					= $(SRCS:%.c=%.o)

CC						= cc
CFLAGS					= -Wall -Wextra -Werror

AR						= ar
ARFLAGS					= rcs

RM						= rm -f

$(NAME)		: $(OBJS)
			$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o			: %.c
			$(CC) $(CFLAGS) -c $< -o $@

all			: $(NAME)

clean		:
			$(RM) $(OBJS)
			$(RM)

fclean		: clean
			$(RM) $(NAME)

re			: fclean all

.PHONY: all clean fclean re