# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 17:25:18 by brhajji-          #+#    #+#              #
#    Updated: 2022/07/12 19:06:56 by brhajji-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = ./srcs

SRCS	= main.c ft_atoi.c ft_lstlast.c utils.c table.c utils2.c


OBJS			=	$(addprefix $(SRC_DIR)/, $(SRCS:%.c=%.o))

NAME			=	philo

CC				=	gcc -pthread

CC2				=	gcc -pthread -g3

CC1				=	gcc -pthread -fsanitize=thread

CFLAGS			=	-Wall -Wextra -Werror

RM				=	rm -f

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS)

all:		${NAME}

ff :	$(OBJS)
	$(CC1) -o $(NAME) $(OBJS)

g3 :	$(OBJS)
	$(CC2) -o $(NAME) $(OBJS)

bonus :		$(BONUS)	
				rm -f $(NAME)

clean:
	${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:			fclean all

.PHONY: 	all clean fclean re
