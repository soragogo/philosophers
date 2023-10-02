NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes
CFLAGS += -g -fsanitize=thread

SRCDIR = srcs

SRCS = main.c \
	ft_atoi.c \
	error_handling.c \
	philo_action.c \
	ft_bzero.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
