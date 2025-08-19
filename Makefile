NAME     = cube3d

SRC_DIRS = srcs libft
INC_DIR  = includes

CFILES   = $(shell find $(SRC_DIRS) -type f -name "*.c")
OFILES   = $(CFILES:.c=.o)

CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
INCLUDES = -I$(INC_DIR)

MLX_DIR     = $(INC_DIR)/MiniLib
MLX_LIB     = $(MLX_DIR)/libmlx.a
MLX_INC     = -I$(MLX_DIR)
MLX_LDFLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OFILES) $(MLX_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INC) -o $(NAME) $(OFILES) $(MLX_LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INC) -c $< -o $@

sanitize: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address -g" all

clean:
	@rm -f $(OFILES)
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all sanitize clean fclean re
