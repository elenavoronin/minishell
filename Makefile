# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: elenavoronin <elnvoronin@gmail.com>          +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/12 11:12:29 by evoronin      #+#    #+#                  #
#    Updated: 2023/11/16 12:04:26 by evoronin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I ./include -g -fsanitize=address

READLINELINKFLAGS := -lreadline
READLINEFLAGS ?= -I/usr/include

VPATH = ./src ./src/libft ./src/lifecycle ./src/parse ./src/execute
SRCS_NAMES = main.c lifecycle_a.c lifecycle_b.c \
parse.c _tokens.c _split_a.c _split_b.c _errors.c \
execute_a.c execute_b.c execute_c.c \
ft_lstnew.c ft_lstadd.c ft_lstsize.c ft_lstlast.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
ft_put_fd.c ft_is.c ft_is2.c ft_converts.c \
ft_calloc.c ft_bzero.c ft_mem.c \
ft_strhelpers.c ft_strfinds.c ft_strmakers.c ft_strmanips.c ft_split.c ft_itoa.c \
ft_lltoa_base.c ft_ltoa_unsigned_base.c ft_atoi_validate.c ft_nums.c \
ft_split2.c ft_joinstrs.c ft_nopes.c ft_free.c \

OBJS_NAMES = $(SRCS_NAMES:.c=.o)
OUT_DIR = ./objs
OBJS = $(addprefix $(OUT_DIR)/,$(OBJS_NAMES))
DEPS = $(OBJS:.o=.d)

all:  $(NAME)
-include $(DEPS)

$(OBJS): $(OUT_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(READLINEFLAGS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(READLINELINKFLAGS)

clean:
	rm -rf $(OUT_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
