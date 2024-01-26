# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: elenavoronin <elnvoronin@gmail.com>          +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/12 11:12:29 by evoronin      #+#    #+#                  #
#    Updated: 2024/01/26 14:05:20 by elenavoroni   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -I ./include -g 
CFLAGS += -fsanitize=address -D DEBUG=0

READLINELINKFLAGS := -lreadline
READLINEFLAGS ?= -I/usr/include

VPATH = ./src ./src/libft ./src/parse ./src/execute ./src/builtins ./src/enviro ./src/signals
SRCS_NAMES = main.c minishell.c enviro.c signals.c \
parse.c _expand.c _split.c _tokenise.c __test.c \
builtins.c env.c echo.c cd.c pwd.c export.c export_check.c unset.c exit.c \
ft_lstnew.c ft_lstadd.c ft_lstsize.c ft_lstlast.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
ft_put_fd.c ft_is.c ft_is2.c ft_converts.c \
ft_calloc.c ft_bzero.c ft_mem.c \
ft_strhelpers.c ft_strfinds.c ft_strmakers.c ft_strmanips.c ft_split.c ft_itoa.c \
ft_lltoa_base.c ft_ltoa_unsigned_base.c ft_atoi_validate.c ft_nums.c \
ft_strcat_free.c ft_split2.c ft_joinstrs.c ft_nopes.c ft_free.c \
execute.c execute_a_pathing.c execute_b_piping.c execute_c_redirecting.c heredoc.c
#execute_a.c execute_b.c execute_c.c execute_d.c 

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
