NAME     = cube3d

SRC_DIRS = srcs libft
INC_DIR  = includes

CFILES = $(shell find $(SRC_DIRS) -type f -name "*.c")
OFILES   = $(CFILES:.c=.o)

CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
INCLUDES = -I$(INC_DIR)

# Detect OS
OS := $(shell uname -s)

ifeq ($(OS),Linux)
	MLX_DIR      = $(INC_DIR)/minilibx-linux
	MLX_INC      = -I$(MLX_DIR)
	MLX_LIB      = $(MLX_DIR)/libmlx.a
	MLX_LDFLAGS  = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
else ifeq ($(OS),Darwin)
	MLX_DIR      = $(INC_DIR)/MiniLib
	MLX_INC      = -I$(MLX_DIR)
	MLX_LIB      = $(MLX_DIR)/libmlx.a
	MLX_LDFLAGS  = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
$(error Unsupported OS: $(OS))
endif

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR) CFLAGS=$(CFLAGS)

$(NAME): $(OFILES) $(MLX_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INC) -o $(NAME) $(OFILES) $(MLX_LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INC) -c $< -o $@

sanitize: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address -g" all

clean:
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all sanitize clean fclean re
