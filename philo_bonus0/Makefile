NAME		=	philo_bonus
HEADER		=	philo_bonus.h
CFLAGS		=	-Wall -Werror -Wextra -pthread
CC			=	clang
SRC			=	philo_bonus.c check_bonus.c eat_bonus.c exit_n_error_bonus.c init_bonus.c utils_bonus.c
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