SRCS = get_next_line.c get_next_line_utils.c main.c
OBJS = $(SRCS:.c=.o)
NAME = get_next_line
CC = cc
BUFFER =  -D BUFFER_SIZE=4
CFLAGS = -Wall -Wextra -Werror $(BUFFER)
RM = rm -f

run: fclean all
	./get_next_line

$(NAME):$(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re