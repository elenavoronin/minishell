# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: elenavoronin <elnvoronin@gmail.com>          +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/12 11:12:29 by evoronin      #+#    #+#                  #
#    Updated: 2023/11/09 14:04:46 by dliu          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ./include -g -fsanitize=address

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	READLINELINKFLAGS := -lreadline -L $(shell brew --prefix readline)/lib
else
	READLINELINKFLAGS := -lreadline
endif

ifeq ($(UNAME_S), Darwin)
	READLINEFLAGS ?= -I $(shell brew --prefix readline)/include
else
	READLINEFLAGS ?= -I/usr/include
endif

NAME = minishell

VPATH = ./src ./src/libft ./src/parse
SRCS_NAMES = main.c parse.c _extract.c _tokens.c _errors.c \
get_next_line.c \
ft_lstnew.c ft_lstadd.c ft_lstsize.c ft_lstlast.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
ft_printf.c ft_printf_helpers.c ft_printf_handle_types.c \
ft_printf_handle_flags.c ft_printf_handle_flags_nums.c \
ft_put_fd.c ft_is.c ft_is2.c ft_converts.c \
ft_calloc.c ft_bzero.c ft_mem.c \
ft_strhelpers.c ft_strfinds.c ft_strmakers.c ft_strmanips.c ft_split.c ft_itoa.c \
ft_lltoa_base.c ft_ltoa_unsigned_base.c ft_atoi_validate.c ft_nums.c \
ft_split2.c ft_joinstrs.c ft_nopes.c ft_free.c

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
