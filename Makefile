CC = gcc
CFLAGS = -W -Werror -Wextra -Wall -ansi -pedantic

NAME =    assembly

SRC =			main.c \
					abilities.c \
					casuals.c \
					casuals2.c \
					stack.c	\
					utils.c

OBJ =     $(SRC:%.c=%.o)

RM =    rm -f

$(NAME)    :    $(OBJ)
					$(CC) $(OBJ) -o $(NAME)

all    : $(NAME)

clean    :
					$(RM) $(OBJ)

fclean    : clean
					$(RM) $(NAME)

re			: fclean all

.PHONY    :    all clean fclean re
