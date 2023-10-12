NAME = so_long
LIBFT_PATH = printf
LIBFT = printf/libftprintf.a
GNL = gnl.a
COMPILER = cc
FLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -lmlx -lXext -lX11

GNL_SRCS = get_next_line_utils_bonus.c get_next_line_bonus.c

GNL_OBJS = $(GNL_SRCS:.c=.o)

ALL_SRCS =	print_error.c \
			check_map.c load_anim.c \
			check_map_extra.c main.c read_map.c \
			draw_fts.c read_map_utils.c \
			player_movement.c load_images.c\

ALL_OBJS = $(ALL_SRCS:.c=.o)

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(ALL_OBJS)
	$(COMPILER) $(FLAGS) $(MLX_FLAGS) $(ALL_OBJS) $(LIBFT) $(GNL) -o $(NAME)
	@ echo "$(GREEN)$(NAME) CREATED! $(CLR_RMV)"

$(LIBFT):
	@ echo "$(YELLOW)Creating libftprintf.a Library.$(CLR_RMV)"
	(cd $(LIBFT_PATH) && make all)
	@ echo "$(GREEN)libftprintf.a Library CREATED!$(CLR_RMV)"

$(GNL): $(LIBFT) $(GNL_OBJS)
	@ echo "$(YELLOW)Creating $(GNL) Library.$(CLR_RMV)"
	ar rcs $(GNL) $(GNL_OBJS)
	@ echo "$(GREEN)$(GNL) Library CREATED!$(CLR_RMV)"

%.o: %.c
	$(COMPILER) $(FLAGS) -c $< -o $@

debug: FLAGS += -g
debug: all

clean:
	@ echo "$(YELLOW)Cleaning ...$(CLR_RMV)"
	rm -f $(ALL_OBJS) $(GNL_OBJS)
	(cd $(LIBFT_PATH) && make clean)
	@ echo "$(GREEN)Cleaned!$(CLR_RMV)"

fclean: clean
	rm -f $(NAME) $(LIBFT) $(GNL)
	@ echo "$(RED)Fully Cleaned$(CLR_RMV)"

re: fclean all

.PHONY: all clean fclean re
