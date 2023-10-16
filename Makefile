NAME = so_long
GNL = gnl.a
LIBFT = libftprintf.a
LIB = libs/
LIBFT_PATH = printf/
GNL_PATH = GNL/
CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -lmlx -lXext -lX11

GNL_SRCS =	src/GNL/get_next_line_bonus.c src/GNL/get_next_line_utils_bonus.c

GNL_OBJS = $(GNL_SRCS:.c=.o)

BON_SRCS =	src/Bonus/animator.c src/Bonus/load_images.c \
			src/Bonus/check_map.c src/Bonus/main.c \
			src/Bonus/check_map_extra.c src/Bonus/map_utils.c \
			src/Bonus/draw_fts.c src/Bonus/player_movement.c \
			src/Bonus/dynamic_list.c src/Bonus/print_error.c \
			src/Bonus/enemy.c src/Bonus/read_map.c \
			src/Bonus/game_utils.c src/Bonus/read_map_utils.c \
			src/Bonus/get_next_line_bonus.c src/Bonus/shortest_path.c \
			src/Bonus/get_next_line_utils_bonus.c src/Bonus/utils.c \
			src/Bonus/load_anim.c \

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

$(NAME): $(LIB)$(LIBFT) $(LIB)$(GNL) $(MAN_OBJS)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(MAN_OBJS) $(LIB)$(GNL) $(LIB)$(LIBFT) -o $(NAME)
	@ echo "$(GREEN)$(NAME) CREATED! $(CLR_RMV)"

$(LIB)$(LIBFT):
	@ echo "$(YELLOW)Creating libftprintf.a Library.$(CLR_RMV)"
	(cd $(LIBFT_PATH) && make all && mv $(LIBFT) ../$(LIB))
	@ echo "$(GREEN)libftprintf.a Library CREATED!$(CLR_RMV)"

$(LIB)$(GNL): $(GNL_OBJS)
	@ echo "$(YELLOW)Creating $(GNL) Library.$(CLR_RMV)"
	ar rcs $(LIB)$(GNL) $(GNL_OBJS)
	@ echo "$(GREEN)$(GNL) Library CREATED!$(CLR_RMV)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
bonus: $(LIB)$(LIBFT) $(LIB)$(GNL) $(BON_OBJS)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(BON_OBJS) $(LIB)$(GNL) $(LIB)$(LIBFT) -o $(NAME)
	@ echo "Bonus $(GREEN)$(NAME) CREATED! $(CLR_RMV)"

clean:
	@ echo "$(YELLOW)Cleaning ...$(CLR_RMV)"
	rm -f $(GNL_OBJS) $(BON_OBJS) $(MAN_OBJS)
	(cd $(LIBFT_PATH) && make clean)
	@ echo "$(GREEN)Cleaned!$(CLR_RMV)"

fclean: clean
	rm -f $(LIB)$(GNL) $(LIB)$(LIBFT) $(NAME)