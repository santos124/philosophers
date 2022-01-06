NAME		=	philo
HEADER		=	philo.h
CFLAGS		=	-Wall -Werror -Wextra
CC			=	clang
SRC			=	main.c ft_atoi.c ft_calloc.c ft_strlen.c
OBJ			=	$(SRC:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJ) $(HEADER) Makefile
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o			:	%.c Makefile $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean		:
			rm -f $(OBJ)

fclean		:	clean
			rm -f $(NAME)

re			:	fclean all

.PHONY: all libft clean fclean re bonus