NAME=codexion

SRC	=	codexion.c \
	 	validation_int.c \
	 	validation_shceduler.c \
	 	parser.c \
		edf_utils.c \
		fifo_utils.c \
		init_all.c \
		init_dongle.c \
		dongle.c \
		time.c \
		coder.c \
		destroy_all.c \
		monitor.c \
		init_coder.c \
		fifo.c \
		edf.c \


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
