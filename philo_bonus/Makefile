NAME		=	philo
HEADER		=	philo.h
CFLAGS		=	-Wall -Werror -Wextra -pthread
CC			=	clang
SRC			=	main.c common_func1.c common_func2.c print_time_func.c philo.c sentinel.c death.c init_room.c
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