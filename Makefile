NAME = minishell
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address 

SRC = ./src/minishell.c \
	  ./src/struct/env/ft_env.c\
	  ./src/buildin/env/ft_env.c\
	  ./src/signals/ft_signals.c\
	  ./src/parsing/ft_parsing.c\
	  ./src/helper/helper_1.c\
	  ./src/helper/helper_2.c\
	  ./src/parsing/ft_check_syntax_error.c\

OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${SRC}   ./libft/libft.a -o ${NAME} -lreadline

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all
