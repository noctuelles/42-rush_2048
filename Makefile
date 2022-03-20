SRC =  srcs/2048.c	\
	   srcs/board.c	\
	   srcs/check_win_lose.c	\
	   srcs/move_horizontal.c	\
	   srcs/move_vertical.c	\
	   srcs/rand.c	\
	   srcs/game_utils.c	

OBJ = $(SRC:.c=.o)

NAME = 2048

HEAD = -I includes

CFLAGS = -Wall -Wextra -Werror

LIB = -lncurses

CC = cc

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(HEAD) $(OBJ) $(LIB) -o $(NAME)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(HEAD) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)

.PHONY : all clean clean re
