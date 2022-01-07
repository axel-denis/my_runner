##
## EPITECH PROJECT, 2021
## bsq
## File description:
## Makefile
##

SRC	=	src/center.c				\
		src/struct_functions.c	\
		src/anims_displays.c	\
		src/frees.c				\
		src/loaders.c			\
		src/utils.c				\
		src/collisions.c		\
		src/events.c			\
		src/menus.c				\
		src/rabbit_run.c		\
		src/endscreens.c		\

OBJ		=		$(SRC:.c=.o)

NAME	=		my_runner # VERIFIER QUE C'EST VALIDE

CFLAGS	+=		-Wall -Wextra

$(NAME):	$(OBJ)
			make -C lib/
			gcc -o $(NAME) $(OBJ) $(CFLAGS) -lcsfml-graphics -lcsfml-system \
			-lcsfml-window -lcsfml-audio -lm -L. ./lib/lib.a

all:		$(NAME)

clean:
			rm -f $(OBJ)
			rm -f criterion_test

fclean: clean
			rm -f $(NAME)

re: fclean all

.PHONY	=	all clean fclean re

#sudo dnf install libasan
#CFLAGS="-fsanitize=address -g3" make re
