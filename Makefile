# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/10 08:23:40 by achauvea          #+#    #+#              #
#    Updated: 2017/01/21 00:42:26 by vdarmaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror
LIBDIR = ./libft/
SRCDIR = ./src/
INCDIR = ./include/

SRC = main.c get_next_line.c core.c env_utils.c list.c error.c echo_builtin.c \
		setenv_builtin.c unsetenv_builtin.c binary.c cd_builtin.c \
		env.c utils.c semicolon.c cd2_builtin.c utils2.c

SRCS = $(addprefix $(SRCDIR), $(SRC))

all: $(NAME)

$(NAME):
	@make -C $(LIBDIR)
	@echo "libft - Compilation Done"	
	@gcc $(FLAGS) $(SRCS) -I$(INCDIR) -o $(NAME) -L $(LIBDIR) -l ft
	@echo "ft_ls - Compilation Done"

clean:
	@make clean -C $(LIBDIR)
	@echo "libft - Clean Done"
	@echo "ft_ls - Clean Done"

fclean: clean
	@make fclean -C $(LIBDIR)
	@rm -rf $(NAME)
	@echo "ft_ls - Fclean Done"

re: fclean all

.PHONY: $(NAME) $(clean) $(fclean) $(re)
