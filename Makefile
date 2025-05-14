CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
NAME = my_readline
SRCS = my_readline.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
