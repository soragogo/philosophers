NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes

ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += -g -fsanitize=thread
endif

SRCDIR = srcs

SRCS = main.c \
	ft_atoi.c \
	ft_strlen.c \
	ft_calloc.c \
	ft_bzero.c \
	ft_strncmp.c \
	flag_manager.c \
	error_handling.c \
	philo_action.c \
	create_forks.c \
	fork_control.c \
	create_threads.c \
	philo_eat.c \
	fork_controll.c \
	philo_sleep.c \
	philo_think.c \
	print_log.c \
	utils.c
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

debug: re

.PHONY: all clean fclean re debug
