NAME = libft.a
COMPILER = cc
FLAGS = -Wall -Werror -Wextra #-std=c99

ALL_SRCS = $(wildcard ft_*.c)
BONUS_SRCS = $(wildcard ft_*_bonus.c)
MANDATORY_SRCS = $(filter-out $(BONUS_SRCS), $(ALL_SRCS))

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
	ar rcs $@ $(MANDATORY_OBJS)

bonus: $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)

%.o: %.c
	$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re