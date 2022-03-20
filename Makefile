SRC = 2048.c	\
	   board.c	\
	   check_win_lose.c	\
	   move_horizontal.c	\
	   move_vertical.c	\
	   rand.c	\
	   win_value.c	\

SRCDIR = src
SRC = $(addprefix $(SRCDIR)/, $(SRC))

OBJ = $(SRC:.c=.o)


NAME = 2048

HEAD = -I ./includes

CFLAGS = -Wall -Wextra -Werror

LIB = -lncurses

CC = cc

$(NAME) :
	make -C ./Libft
	$(CC) $(CFLAGS) $(OBJ) $(HEAD) $(LIB) -o $(NAME)

all : $(NAME)

clean :
	make clean -C ./Libft
	rm -f $(OBJ)

fclean :
	make fclean -C ./Libft
	rm -f $(OBJ)
	rm -f $(NAME)

re : fclean $(NAME)

.PHONY : all clean clean re
