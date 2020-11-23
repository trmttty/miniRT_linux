CC				= gcc
FLAGS			= -Wall -Wextra -Werror
NAME 			= miniRT
SRC_RT_DIR 		= ./src/
OBJ_DIR 		= ./obj/
LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
MINILIBX_DIR	= minilibx-linux
MINILIBX		= $(MINILIBX_DIR)/libmlx.a
INC				=/usr/include
INCLIB			=$(INC)/../lib

SRC_RT = main.c \
			get_next_line.c \
			parse.c \
			parse_resolution.c \
			parse_ambient.c \
			parse_camera.c \
			parse_light.c \
			parse_sphere.c \
			parse_plane.c \
			parse_square.c \
			parse_cylinder.c \
			parse_triangle.c \
			parse_utils_1.c \
			parse_utils_2.c \
			create_img.c \
			put_img.c \
			raytrace_setting.c \
			raytrace_1.c \
			raytrace_2.c \
			vector_1.c \
			vector_2.c \
			color_utils.c \
			bmp.c \
			error.c \
			find_cylinder.c \
			find_intersection.c \
			find_plane.c \
			find_sphere.c \
			find_square.c \
			find_triangle.c \
			utils.c

OBJ_RT = $(addprefix $(OBJ_DIR),$(SRC_RT:%.c=%.o))
OBJ = $(OBJ_RT)
HEADERS = includes

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ_DIR) $(OBJ_RT)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L minilibx-linux -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd -L libft -lft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_RT_DIR)%.c
	$(CC) $(FLAGS) -I $(HEADERS) -o $@ -c $<

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
