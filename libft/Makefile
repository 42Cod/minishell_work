# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkolle <nkolle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/07 15:33:26 by nkolle            #+#    #+#              #
#    Updated: 2022/06/02 19:29:25 by nkolle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRC = ft_isalnum.c\
	ft_strjoin.c\
	ft_split.c\
	ft_strnstr.c\
	ft_strlen.c \
	ft_atoi.c\
	ft_memcpy.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_strlcpy.c\
	ft_memmove.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memset.c\
	ft_strlcat.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strnstr.c\
	ft_strncmp.c\
	ft_strlen.c\
	ft_isalpha.c\
	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_calloc.c\
	ft_strdup.c\
	ft_substr.c\
	ft_strjoin_free.c\
	ft_strtrim.c\
	ft_itoa.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_strmapi.c\
	ft_striteri.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c


BNS = ft_lstnew.c\
	ft_lstadd_front.c\
	ft_lstsize.c\
	ft_lstadd_back.c\
	ft_lstlast.c\
	ft_lstclear.c\
	ft_lstmap.c\
	ft_lstiter.c\
	ft_lstdelone.c


all: $(NAME)

$(NAME): *.c
	$(CC) $(FLAGS) -c $(SRC)
	ar rc $(NAME) *.o

bonus:
	$(CC) $(FLAGS) -c $(BNS)
	ar rc $(NAME) *.o

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
