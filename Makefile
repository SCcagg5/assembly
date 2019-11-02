CC = gcc
CFLAGS = -W -Werror -Wextra -Wall -ansi -pedantic

NAME =    not_mg

SRC =    main.c 

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
