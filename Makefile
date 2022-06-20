.PHONY:	clean fclean re all

NAME	:= philo
CFLAGS	:= -Wall -Wextra -Werror -pthread
CC		:= gcc
SRC		:=	main.c \
			utils.c \
			start.c \
			philosopher.c \
			status.c \
			end.c

SRC_FOLDER 	:= src
OBJ_FOLDER	:= obj
SRCS 		:= $(addprefix ${SRC_FOLDER}/, ${SRC})
OBJS 		:= $(addprefix ${OBJ_FOLDER}/, ${SRCS:.c=.o})

all	: $(NAME)

$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJS) : $(OBJ_FOLDER)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_FOLDER)

fclean: clean
	rm -f $(NAME)

re	: fclean all
