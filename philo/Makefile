NAME		=	philo
HEADER		=	philo.h
CFLAGS		=	-Wall -Werror -Wextra -pthread
CC			=	clang
SRC			=	main.c common_func1.c common_func2.c do.c fork.c
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