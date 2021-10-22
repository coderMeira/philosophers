
# -*- MakeFile -*-

MAKEFLAGS	+= -s

CFLAGS		= -Wall -Werror -Wextra -g -pthread #-fsanitize=thread

NAME		= philo

SRCS		= ${wildcard src/*.c}

OBJS		= $(SRCS:.c=.o)

.o: .c
	gcc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	echo "Compiling ${NAME}"
	gcc $(CFLAGS) $(OBJS) -o $(NAME)
	mkdir -p obj
	mv ${OBJS} obj
	echo "Ready to use!"

debug:
	gcc $(CFLAGS) $(SRCS) -o debug

clean:
	rm -rf obj ${OBJS}
	echo "Objects cleaned"

fclean:
	rm -rf obj ${OBJS} $(NAME)
	echo "${NAME} and objects cleaned"

dclean:
	rm -rf obj ${OBJS} debug debug.dSYM
	echo "debug and objects cleaned"

re: fclean all

.PHONY:	all clean fclean re
