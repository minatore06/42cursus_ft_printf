CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=libftprintf.a

FILES=ft_printf.c
OBJECTS=$(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
	$(MAKE) clean -C libft

fckeab: clean
	rm -f $(NAME)

re:	fclean $(NAME)

.PHONY:	all clean fclean re
