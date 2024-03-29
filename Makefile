NAME = minishell
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address 


SRC = ./src/minishell.c \
	  ./src/struct/env/ft_env.c\
	  ./src/buildin/env/ft_env.c\
	  ./src/signals/ft_signals.c\
	  ./src/parsing/ft_parsing.c\
	  ./src/helper/helper_1.c\
	  ./src/helper/helper_2.c\
	  ./src/free/free.c\
	  ./src/parsing/ft_check_syntax_error.c\
	  ./src/parsing/ft_add_space_to_input.c\
	  ./src/parsing/ft_add_space_to_output.c\
	  ./src/parsing/ft_add_space_to_pipe.c\
	  ./src/struct/pipe/ft_pipe.c\
	  ./src/struct/tree/ft_tree.c\
	  ./src/execution/ft_execution.c\
	  ./src/execution/ft_handle_child.c\
	  ./src/execution/ft_handle_heredoc.c\

OBJ = ${SRC:.c=.o}
all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${SRC}   ./libft/libft.a -o ${NAME} -lreadline


clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all
