
# -*- MakeFile -*-

MAKEFLAGS	+= -s

CFLAGS		= -Wall -Werror -Wextra -g

NAME		= philosophers

LIBFT_DIR	= lib/libft/src
LIBFT_EXEC	= lib/libft/bin/libft.a

SRCS		= ${wildcard src/*.c}

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT_EXEC) $(OBJS)
	echo "Compiling ${NAME}"
	gcc $(CFLAGS) $(LIBFT_EXEC) $(OBJS) -o $(NAME)
	mkdir -p obj
	mv ${OBJS} obj
	echo "Ready to use!"

$(LIBFT_EXEC):
	echo "Compiling libft"
	${MAKE} -C $(LIBFT_DIR)
	echo "Libft compiled"

clean:
	rm -rf obj ${OBJS}
	${MAKE} -C $(LIBFT_DIR) fclean
	echo "Objects cleaned"

fclean:
	rm -rf obj ${OBJS} $(NAME)
	${MAKE} -C $(LIBFT_DIR) fclean
	echo "${NAME} and objects cleaned"

re: fclean all

.PHONY:	all clean fclean re
