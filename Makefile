# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olcherno <olcherno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 15:18:15 by olcherno          #+#    #+#              #
#    Updated: 2025/06/18 15:13:59 by olcherno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Компілятор і флаги
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Імена
NAME = cub3d

# Шляхи
SRCDIR = src
OBJDIR = obj
LIBFTDIR = libs/libft
MLXDIR = libs/minilibx

# Флаги лінкування
MLX_FLAGS = -L$(MLXDIR) -lmlx -lX11 -lXext -lm
LIBS = -L$(LIBFTDIR) -lft

# Список файлів
SRC = main.c window.c window1.c
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# Основне правило
$(NAME): $(OBJS) $(LIBFTDIR)/libft.a $(MLXDIR)/libmlx.a
	$(CC) $(CFLAGS) -no-pie $(OBJS) $(LIBS) $(MLX_FLAGS) -o $(NAME)

# Компіляція .c → .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I. -I$(LIBFTDIR) -I$(MLXDIR) -c $< -o $@

# Створення obj/
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Збірка бібліотек
$(LIBFTDIR)/libft.a:
	$(MAKE) -C $(LIBFTDIR)

$(MLXDIR)/libmlx.a:
	$(MAKE) -C $(MLXDIR)

all: $(NAME)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(MLXDIR) clean

re: fclean all

# Стандартні правила
.PHONY: all clean fclean re