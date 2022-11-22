CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=libftprintf.a

FILES=ft_printf.c ft_printf_manage_flags1.c ft_printf_manage_flags2.c ft_printf_manage_flags_master.c ft_printf_manage_nbr.c ft_printf_manage_ptr.c ft_printf_put.c ft_printf_utils.c
OBJECTS=$(FILES:.c=.o)

LIBFT=libft
LIBFTNAME=libft.a

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C $(LIBFT)
	mv $(LIBFT)/$(LIBFTNAME) $(NAME)
	ar rcs $(NAME) $(OBJECTS)

bonus: all

clean:
	rm -f $(OBJECTS)
	$(MAKE) clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/$(LIBFTNAME)

re:	fclean all

.PHONY:	all clean fclean re
