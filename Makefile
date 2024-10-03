# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdahlstr <mdahlstr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 10:08:59 by mdahlstr          #+#    #+#              #
#    Updated: 2024/10/03 11:12:34 by mdahlstr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Config: name of executable, compiler and its flags                  
NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./MLX42/include

# Source files
SRCS = so_long.c

# Object files (replace .c with .o)
SO_LONG_OBJS = $(SRCS:.c=.o)

# Libft directory and source files
LIBFT_DIR = ./libft
LIBFT_SRCS = $(wildcard $(LIBFT_DIR)/*.c)  # Get all .c files in libft
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)  # Corresponding .o files

# MLX42 directory and object files
MLX42_DIR = ./MLX42
MLX42_BUILD_DIR = $(MLX42_DIR)/build
MLX42_LIB = $(MLX42_BUILD_DIR)/libmlx42.a

# Default target
# all: $(LIBFT_OBJS) $(MLX42_LIB) $(NAME)
all: $(LIBFT_DIR)/libft.a $(MLX42_LIB) $(NAME)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build the libft library
$(LIBFT_DIR)/libft.a: $(LIBFT_OBJS)
	$(MAKE) -C $(LIBFT_DIR)

# Clone MLX42, generate build files with CMake, and build it
$(MLX42_LIB):
	if [ ! -d "$(MLX42_DIR)" ]; then git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); fi
	mkdir -p $(MLX42_BUILD_DIR)
	cmake -B $(MLX42_BUILD_DIR) -S $(MLX42_DIR)
	cmake --build $(MLX42_BUILD_DIR)

# Rule to create the executable
$(NAME): $(SO_LONG_OBJS) $(LIBFT_OBJS) $(MLX42_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(SO_LONG_OBJS) -L$(LIBFT_DIR) -lft -L$(MLX42_BUILD_DIR) -lmlx42

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