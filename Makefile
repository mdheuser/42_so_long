# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 10:08:59 by mdahlstr          #+#    #+#              #
#    Updated: 2024/10/28 20:48:26 by mdahlstr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Config: name of executable, compiler and flags                  
NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./mlx/include -Iincludes

# Source files // I can use "addprefix" to mention "./src" only once.
# SRCS = ./src/main.c ./src/command_line_args.c # ./src/open_map.c
SRCS = ./src/main.c ./src/validate_args.c ./src/read_map.c ./src/get_map_dimensions.c \
		./src/validate_map.c ./src/render_images.c ./src/render_static_map.c \
		./src/load_images.c ./src/initialise_game.c ./src/manage_motion.c \
		./src/manage_motion2.c ./src/counters.c ./src/win_game.c ./src/cleanup_game.c \
		./src/validate_path.c

# Object files (replace .c with .o)
SO_LONG_OBJS = $(SRCS:.c=.o)

# Libft directory and source files
LIBFT_DIR = ./libs/libft
LIBFT_SRCS = $(wildcard $(LIBFT_DIR)/*.c)  # Get all .c files in libft // IS THIS FORBIDDEN?
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)  # Corresponding .o files

# MLX42 directory and object files
MLX42_DIR = ./libs/mlx
MLX42_BUILD_DIR = $(MLX42_DIR)/build
MLX42_LIB = $(MLX42_BUILD_DIR)/libmlx42.a

# Default target
all: $(LIBFT_DIR)/libft.a $(MLX42_LIB) $(NAME)

# MLX42 is dependent on other libraries (dl-dynamically loaded, glfw-graphics library framework, m-math)
MLXLIB_FLAGS = -ldl -lglfw -lm

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build the libft library
$(LIBFT_DIR)/libft.a: # $(LIBFT_OBJS)
	$(MAKE) -C $(LIBFT_DIR)

# Clone MLX42, generate build files with CMake, and build it
$(MLX42_LIB):
	if [ ! -d "$(MLX42_DIR)" ]; \
	then git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); fi
	mkdir -p $(MLX42_BUILD_DIR)
	cmake -B $(MLX42_BUILD_DIR) -S $(MLX42_DIR) -DDEBUG=1
	cmake --build $(MLX42_BUILD_DIR)

# Rule to create the executable
$(NAME): $(SO_LONG_OBJS) $(LIBFT_DIR)/libft.a
	$(CC) -g $(CFLAGS) -o $(NAME) $(SO_LONG_OBJS) \
	-L$(LIBFT_DIR) -lft -L$(MLX42_BUILD_DIR) -lmlx42 $(MLXLIB_FLAGS)

# Clean up object files
clean:
	rm -f $(SO_LONG_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(MLX42_BUILD_DIR)

# Clean up object files and the executables
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX42_DIR)

# Rebuild the executables
re: fclean all

# Prevent unnecessary relinking
.PHONY: all clean fclean re