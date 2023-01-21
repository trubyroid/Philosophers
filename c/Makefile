NAME = philo
HEAD = ./philosophers.h
CFLAGS = -Wall -Wextra -Werror
C_FILE = main.c check_n_parse.c	philo.c extra_functions.c lib.c
O_FILE = $(C_FILE:.c=.o)

all:
	$(MAKE) $(NAME)
$(NAME): $(O_FILE)
	gcc -g $(O_FILE) -o $(NAME)

.PHONY: all clean fclean re

%.o: %.c $(HEAD)
	gcc -c -g $(СFLAGS) $< -o $@

clean:
	@rm -f $(O_FILE)
fclean: clean
	@rm -f $(NAME)
re: fclean all