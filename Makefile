SRC1			= 	client \

SRC2			=	server \

SRCS1		= $(addsuffix .c, ${SRC1})

SRCS2		= $(addsuffix .c, ${SRC2})

OBJS1		= ${SRCS1:.c=.o}

OBJS2		= ${SRCS2:.c=.o}

NAME1		= client

NAME2		= server

CC			= gcc
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

all:		$(NAME1) $(NAME2)

$(NAME1):	${OBJS1}
			${CC} ${CFLAGS} ${OBJS1} -o ${NAME1}

$(NAME2):	${OBJS2}
			${CC} ${CFLAGS} ${OBJS2} -o ${NAME2}

clean:
			${RM} ${OBJS1}
			${RM} ${OBJS2}

fclean:		clean
			${RM} $(NAME1)
			${RM} $(NAME2)

re:			fclean all

.PHONY:		all clean fclean re
