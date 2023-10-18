NAME = so_long
NAME_B = so_long_bonus
GNL = src/GNL/gnl.a
LIBFT = printf/libftprintf.a
LIBFT_PATH = printf/
CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -lmlx -lXext -lX11

GNL_SRCS =	src/GNL/get_next_line_bonus.c src/GNL/get_next_line_utils_bonus.c

GNL_OBJS = $(GNL_SRCS:.c=.o)

BON_SRCS =	src/Bonus/animator_bonus.c src/Bonus/load_anim_bonus.c \
			src/Bonus/check_map_bonus.c src/Bonus/load_images_bonus.c \
			src/Bonus/check_map_extra_bonus.c src/Bonus/main_bonus.c \
			src/Bonus/draw_fts_bonus.c src/Bonus/map_utils_bonus.c \
			src/Bonus/dynamic_list_bonus.c src/Bonus/player_movement_bonus.c \
			src/Bonus/enemy_bonus.c src/Bonus/print_error_bonus.c \
			src/Bonus/enemy_utils_bonus.c src/Bonus/read_map_bonus.c \
			src/Bonus/game_utils_bonus.c src/Bonus/read_map_utils_bonus.c \
			src/Bonus/shortest_path_bonus.c src/Bonus/utils_bonus.c \


BON_OBJS = $(BON_SRCS:.c=.o)

MAN_SRCS := src/Mandatory/check_map.c src/Mandatory/load_anim.c src/Mandatory/read_map.c \
			src/Mandatory/check_map_extra.c src/Mandatory/load_images.c src/Mandatory/read_map_utils.c \
			src/Mandatory/draw_fts.c src/Mandatory/main.c src/Mandatory/shortest_path.c \
			src/Mandatory/dynamic_list.c src/Mandatory/player_movement.c src/Mandatory/utils.c \
			src/Mandatory/game_utils.c src/Mandatory/print_error.c \

MAN_OBJS = $(MAN_SRCS:.c=.o)

CLR_RMV		:= \033[0m	
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(MAN_OBJS)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(MAN_OBJS) $(GNL) $(LIBFT) -o $(NAME)
	@ echo "$(GREEN)$(NAME) CREATED! $(CLR_RMV)"

$(NAME_B): $(LIBFT) $(GNL) $(BON_OBJS)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(BON_OBJS) $(GNL) $(LIBFT) -o $(NAME_B)
	@ echo "$(GREEN)$(NAME_B) CREATED! $(CLR_RMV)"

$(LIBFT):
	@ echo "$(YELLOW)Creating libftprintf.a Library.$(CLR_RMV)"
	(cd $(LIBFT_PATH) && make all)
	@ echo "$(GREEN)libftprintf.a Library CREATED!$(CLR_RMV)"

$(GNL): $(GNL_OBJS)
	@ echo "$(YELLOW)Creating $(GNL) Library.$(CLR_RMV)"
	ar rcs $(GNL) $(GNL_OBJS)
	@ echo "$(GREEN)$(GNL) Library CREATED!$(CLR_RMV)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_B)

clean:
	@ echo "$(YELLOW)Cleaning ...$(CLR_RMV)"
	rm -f $(GNL_OBJS) $(BON_OBJS) $(MAN_OBJS)
	(cd $(LIBFT_PATH) && make clean)
	@ echo "$(GREEN)Cleaned!$(CLR_RMV)"

fclean: clean
	(cd $(LIBFT_PATH) && make fclean)
	rm -f $(GNL) $(LIBFT) $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re bonus