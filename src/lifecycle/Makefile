# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: elenavoronin <elnvoronin@gmail.com>          +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/12 11:12:29 by evoronin      #+#    #+#                  #
#    Updated: 2023/11/07 17:22:54 by evoronin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ../../include  -g

READLINELINKFLAGS := -lreadline
READLINEFLAGS ?= -I/usr/include

NAME = lifecycle

SRCS_NAMES = lifecycle_main.c lifecycle_a.c lifecycle_b.c\
../libft/ft_atoi_validate.c \
../libft/ft_bzero.c \
../libft/ft_calloc.c \
../libft/ft_converts.c \
../libft/ft_free.c \
../libft/ft_is.c \
../libft/ft_itoa.c \
../libft/ft_joinstrs.c \
../libft/ft_lltoa_base.c \
../libft/ft_lstadd.c \
../libft/ft_lstclear.c \
../libft/ft_lstiter.c \
../libft/ft_lstlast.c \
../libft/ft_lstmap.c \
../libft/ft_lstnew.c \
../libft/ft_lstsize.c \
../libft/ft_ltoa_unsigned_base.c \
../libft/ft_mem.c \
../libft/ft_nopes.c \
../libft/ft_nums.c \
../libft/ft_put_fd.c \
../libft/ft_split.c \
../libft/ft_split2.c \
../libft/ft_strfinds.c \
../libft/ft_strhelpers.c \
../libft/ft_strmakers.c \
../libft/ft_strmanips.c \
../libft/get_next_line.c \


OBJS_NAMES = $(SRCS_NAMES:.c=.o)
OBJS = $(OBJS_NAMES)

all:  $(NAME)

$(OBJS): %.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(READLINEFLAGS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(READLINELINKFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
