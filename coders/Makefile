NAME=codexion

SRC	=	codexion.c \
	 	validation_int.c \
	 	validation_shceduler.c \
	 	parser.c \

OBJS = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g
RM = rm -rf

$(NAME): $(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

all: $(NAME)

clean: 
	$(RM) $(OBJS) 

fclean: clean
	$(RM) $(NAME)

re: fclean all
so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC)
	gcc -nostartfiles -shared -o libft.so $(OBJ)

.PHONY:	all clean fclean re so
