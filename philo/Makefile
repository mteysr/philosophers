NAME = philo

SRCS = main.c philo_utils.c init.c loop.c libft_func.c controls.c

OBJS = main.o philo_utils.o init.o loop.o libft_func.o controls.o

FLAG = -Wall -Wextra -Werror

CC = gcc

FLAGS_DATARACE = -fsanitize=thread -g

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAG) $(OBJS) -o $(NAME)

data_race:
	$(CC) $(FLAGS_DATARACE) $(SRCS) -o $(NAME)

clean :
	rm -rf main.o philo_utils.o loop.o init.o libft_func.o controls.o

fclean : clean 
	rm -rf $(NAME)

re : fclean all

.PHONY : all fclean clean re
