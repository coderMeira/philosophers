
# -*- MakeFile -*-

MAKEFLAGS	+= -s

CFLAGS		= -Wall -Werror -Wextra -g -pthread

NAME		= philo

SRCS		= ${wildcard src/*.c}

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	echo "Compiling ${NAME}"
	gcc $(CFLAGS) $(OBJS) -o $(NAME)
	mkdir -p obj
	mv ${OBJS} obj
	echo "Ready to use!"

clean:
	rm -rf obj ${OBJS}
	echo "Objects cleaned"

fclean:
	rm -rf obj ${OBJS} $(NAME)
	echo "${NAME} and objects cleaned"

re: fclean all

.PHONY:	all clean fclean re
