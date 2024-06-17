NAME = cub3d

BOLD_GREEN		= \033[32;01m
BOLD_CYAN		= \033[36;01m
GREEN			= \033[0;32m
YELLOW			= \033[0;33m
RESET			= \033[0m

SRCS = srcs/
INCLUDE = include/
MLX_PATH = mlx/
MLX_LIB = libmlx_Linux.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lX11 -lXext

FILES = main.c map.c assets.c player.c raycasting.c utils.c gnl.c utils_gnl.c

OBJECTS = $(addprefix $(SRCS), $(FILES:.c=.o))

BONUS_MODE = 0

%.o: %.c
	@echo "$(BOLD_CYAN)$(NAME) $(RESET)[$(GREEN)$@$(RESET)] : $(YELLOW)Creating object$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ -lm -D BONUS_MODE=$(BONUS_MODE)

all: mlx $(NAME)

#mlx:
#	@make -sC $(MLX_PATH)

$(NAME): $(OBJECTS)
	@echo "$(BOLD_CYAN)$(NAME) $(RESET)[$(GREEN)$@$(RESET)] : $(YELLOW)Compiling $@$(RESET)"
	@$(CC) $(CFLAGS) $(OBJECTS) $(MLX_PATH)$(MLX_LIB) $(MLXFLAGS) -o $@ -lm -I$(MLX_PATH) -I$(INCLUDE)
	@echo "\n$(BOLD_GREEN)=== $(NAME) successfully compiled! ===$(RESET)\n"

bonus: BONUS_MODE = 1
bonus: clean mlx $(NAME)

clean:
	@echo "$(BOLD_CYAN)$(NAME) $(RESET)[$(GREEN)$@$(RESET)] : Removing objects"
	@rm -rf $(OBJECTS)

fclean: clean
	@echo "$(BOLD_CYAN)$(NAME) $(RESET)[$(GREEN)$@$(RESET)] : Removing $(NAME)"
	@rm -rf $(NAME)
#	@make clean -sC $(MLX_PATH)

re: fclean all

.PHONY: mlx