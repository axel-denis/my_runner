##
## EPITECH PROJECT, 2021
## bsq
## File description:
## Makefile
##

SRC	=	src/main.c				\
		src/struct_functions.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_runner # VERIFIER QUE C'EST VALIDE

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -lcsfml-graphics -lcsfml-system -lcsfml-window -lm \
	-Wall -Wextra -Werror

clean:
	rm -f $(OBJ)
	rm -f criterion_test

fclean: clean
	rm -f $(NAME)

re: fclean all
