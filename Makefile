NAME    = cube3d

SRC_DIRS = srcs libft
INC_DIR  = includes

CFILES  = $(shell find $(SRC_DIRS) -type f -name "*.c")
OFILES  = $(CFILES:.c=.o)

CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
INCLUDES = -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OFILES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

sanitize: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address -g" $(NAME)

clean:
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all sanitize clean fclean re
