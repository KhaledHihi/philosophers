
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = main.c helper.c init.c simulation.c the_monitor.c
OBJ = $(SRC:.c=.o)
RM = rm -f
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(MAKE) clean -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	$(MAKE) clean

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
