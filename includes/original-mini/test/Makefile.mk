MLX_DIR=..

all: $(MLX_DIR)/libmlx.a $(NAME)

$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)