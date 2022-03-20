SRC = 2048.c	\
	   board.c	\
	   check_win_lose.c	\
	   move_horizontal.c	\
	   move_vertical.c	\
	   rand.c	\
	   game_utils.c	

SRCDIR = src
#SRC = $(addprefix $(SRCDIR)/, $(SRC))

OBJ = $(SRC:.c=.o)


NAME = 2048

HEAD = -I ./includes

CFLAGS = -Wall -Wextra -Werror

LIB = -lncurses

CC = cc

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(HEAD) $(LIB) -o $(NAME)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $<
clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)

.PHONY : all clean clean re
