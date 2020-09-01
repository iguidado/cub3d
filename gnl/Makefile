# Name

NAME = libgnl.a

# File

SRC = get_next_line.c\
	get_next_line_utils.c\

HDR = get_next_line.h

# Compiler

CC = clang
F_WRN = -Wall -Werror -Wall
F_DEF = -DBUFFER_SIZE=32
FLAG = $(F_WRN) $(F_DEF)

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o : %.c $(HDR)
	$(CC) $(FLAG) -o $@ -c $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
