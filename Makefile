
NAME	=	microshell

SRCS	=	microshell.c ft_parser.c ft_executor.c

OBJS	=	${SRCS:.c=.o}

HEADER	=	microshell.h

CC		=	gcc
FLAGS	=	-Wall -Werror -Wextra

RM		=	rm -rf

.PHONY	:	all clean fclean re

all		:	${NAME}

${NAME}	:	${OBJS}
			@${CC} ${FLAGS} -I${HEADER} ${OBJS} -o ${NAME}
			@printf "File '${NAME}' is created!\n"

clean	:	
			@${RM} ${OBJS}
			@printf "Files '${OBJS}' are clean!\n"

fclean	:	clean
			@${RM} ${NAME}
			@printf "File '${NAME}' is clean!\n"

re		:	fclean all