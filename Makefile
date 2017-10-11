# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 15:56:40 by gmichaud          #+#    #+#              #
#    Updated: 2017/10/11 16:52:54 by gmichaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC_PATH = src

LIBS = -lft -lmlx -lm -lpthread -framework OpenGL -framework Appkit

SRC_NAME = main.c display.c draw_fractal.c inputs.c \
	fractal_calc_1.c color.c quit.c mouse.c img_util.c fractal_calc_2.c \
	threading.c ft_ftoa.c ft_lltoa.c ft_e_ftoa.c init_args.c

OBJ_PATH = obj

INC_PATH = -I./includes -I./libft/includes -I./mlxext/includes \
	-I./minilibx_macos

LIB_PATH = -L./libft -L./minilibx_macos

CC = clang

CFLAGS = -Wall -Wextra -Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft
	make -C ./minilibx_macos
	$(CC) $(CFLAGS) $^ -o $@ $(LIB_PATH) $(LIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) -c -o $@ $< $(INC_PATH)

clean:
	/bin/rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	make -C ./libft clean
	make -C ./minilibx_macos clean

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f ./libft/libft.a
	/bin/rm -f ./minilibx_macos/libmlx.a

re: fclean $(NAME)
