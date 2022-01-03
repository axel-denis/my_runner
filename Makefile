##
## EPITECH PROJECT, 2021
## bsq
## File description:
## Makefile
##

SRC	=	src/main.c				\
		src/struct_functions.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	my_runner # VERIFIER QUE C'EST VALIDE

CFLAGS	+=	-Wall -Wextra

$(NAME):	$(OBJ)
	make -C lib/
	gcc -o $(NAME) $(OBJ) $(CFLAGS) -lcsfml-graphics -lcsfml-system -lcsfml-window -lm \
	-L. ./lib/lib.a

all:	$(NAME)

clean:
	rm -f $(OBJ)
	rm -f criterion_test

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY	=	all clean fclean re

#sudo dnf install libasan
#CFLAGS="-fsanitize=address -g3" make re
