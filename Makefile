SRCS = get_next_line.c get_next_line_utils.c main.c
OBJS = $(SRCS:.c=.o)
NAME = get_next_line
CC = cc
BUFFER = 
CFLAGS = -Wall -Wextra -Werror $(BUFFER)
RM = rm -f



$(NAME):$(OBJS)
	@$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: fclean all
	./get_next_line
.PHONY: all clean fclean re