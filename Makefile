NAME = ft_ls
#LD = -Llibft -lft
LD = libft/*.o
INC = -I libft
FLAGS = $(INC) $(LD) 
SRCS = main.c ft_ls.c read_dir.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	#@make -C libft
	gcc -g3 $(LD) $^ -o $(NAME)

%.o: %.c
	gcc -g3 $(INC) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make all

tests:
	@./tests	
run: all
	@./test1
