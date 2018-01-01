NAME = ft_ls
#LD = -Llibft -lft
LD = libft/*.o
INC = -I libft -I .
FLAGS = $(INC) $(LD) 
SRCS = main.c ft_ls.c read_dir.c
OBJS = $(SRCS:%.c=%.o)

VPATH = srcs:objs

all: $(OBJS)
	gcc -g3 $(LD) $^ -o $(NAME)

$(NAME):
	@make -C libft

%.o: %.c
	gcc -g3 $(INC) -c $< -o objs/$@

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
