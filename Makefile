##
## EPITECH PROJECT, 2020
## CNA_trade_2019
## File description:
## Makefile
##

SRC		= 	src/main.cpp		\
			src/Trade.cpp		\

OBJ	=	$(SRC:.cpp=.o)

CFLAGS	+=	-Wall -Wextra -Werror -g3

NAME	=	trade

all:		build

build:		$(OBJ)
		clang++ -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f *~
		rm -f $(NAME)
		rm -f vgcore.*

re:		fclean all

.PHONY:		make clean fclean re