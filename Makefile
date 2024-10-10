NAME = cub3d

BOLD_GREEN		= \033[32;01m
BOLD_CYAN		= \033[36;01m
GREEN			= \033[0;32m
YELLOW			= \033[0;33m
RESET			= \033[0m

SRCS = srcs/
SRCS_BONUS = srcs_bonus/
INCLUDE = include/
MLX_PATH = mlx/
MLX_LIB = libmlx_Linux.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -g
MLXFLAGS = -lX11 -lXext

FILES = main.c hooks.c map_1.c map_2.c map_3.c init.c  \
		assets.c player.c raycasting.c \
		utils_1.c utils_2.c utils_3.c gnl.c utils_gnl.c
OBJECTS = $(addprefix $(SRCS), $(FILES:.c=.o))
FILES_BONUS = main.c close_game.c hooks_1.c hooks_2.c map.c init.c  \
			assets.c player.c portals.c enemies_1.c enemies_2.c enemies_3.c enemies_4.c \
			gui_1.c gui_2.c minimap.c textures.c get_texture_1.c get_texture_2.c \
			raycasting_1.c raycasting_2.c raycasting_3.c \
			z_buffer_1.c z_buffer_2.c \
			utils_1.c utils_2.c utils_3.c \
			utils_raycasting_1.c utils_raycasting_2.c utils_raycasting_3.c \
			gnl.c utils_gnl.c sound.c
OBJECTS_BONUS = $(addprefix $(SRCS_BONUS), $(FILES_BONUS:.c=.o))

%.o: %.c
	@echo "$(BOLD_CYAN)$(NAME) $(RESET)[$(GREEN)$@$(RESET)] : $(YELLOW)Creating object$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ -lm

all: mlx $(NAME)

mlx:
	@make -sC $(MLX_PATH)

$(NAME): $(OBJECTS)
	@echo "$(BOLD_CYAN)$(NAME) $(RESET)[$(GREEN)$@$(RESET)] : $(YELLOW)Compiling $@$(RESET)"
	@$(CC) $(CFLAGS) $(OBJECTS) $(MLX_PATH)$(MLX_LIB) $(MLXFLAGS) -o $@ -lpulse -lm -I$(MLX_PATH) -I$(INCLUDE)
	@echo "\n$(BOLD_GREEN)=== $@ successfully compiled! ===$(RESET)\n"

bonus: mlx $(OBJECTS_BONUS)
	@echo "$(BOLD_CYAN)$(NAME) $(RESET)[$(GREEN)$(NAME)$(RESET)] : $(YELLOW)Compiling $(NAME) (bonus)$(RESET)"
	@$(CC) $(CFLAGS) $(OBJECTS_BONUS) $(MLX_PATH)$(MLX_LIB) $(MLXFLAGS) -o $(NAME) -lm -I$(MLX_PATH) -I$(INCLUDE)
	@echo "\n$(BOLD_GREEN)=== $(NAME) successfully compiled! ===$(RESET)\n"

clean:
	@echo "$(BOLD_CYAN)$(NAME) $(RESET)[$(GREEN)$@$(RESET)] : Removing objects"
	@rm -rf $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	@echo "$(BOLD_CYAN)$(NAME) $(RESET)[$(GREEN)$@$(RESET)] : Removing $(NAME)"
	@rm -rf $(NAME)
	@make clean -sC $(MLX_PATH)

re: fclean all

rebonus: fclean bonus

.PHONY: mlx