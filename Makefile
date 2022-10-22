CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=libftprintf.a

FILES=ft_printf.c
OBJECTS=$(FILES:.c=.o)

LIBFT=libft
LIBFTNAME=libft.a

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C $(LIBFT)
	mv $(LIBFT)/$(LIBFTNAME) $(NAME)
	ar rcs $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
	$(MAKE) clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/$(LIBFTNAME)

re:	fclean all

.PHONY:	all clean fclean re
