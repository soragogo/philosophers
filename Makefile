NAME = philosophers

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes

SRCDIR = srcs

SRCS = test.c \
	ft_atoi.c \
	error_handling.c

SRCFILES = $(addprefix $(SRCDIR)/, $(SRCS))

OBJDIR = objs

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
