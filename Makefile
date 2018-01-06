NAME = ft_ls
#LD = -Llibft -lft
LD = libft/*.o
INC = -I libft -I .
FLAGS = $(INC) $(LD) 
SRCS = main.c ft_ls.c read_dir.c print.c mklist.c print2.c
OBJS = $(SRCS:.c=.o)

vpath %.c srcs
vpath %.o objs

all: $(OBJS)
	gcc -g3 $(LD) $^ -o $(NAME)

$(NAME): $(OBJS)
	@make -C libft

%.o:%.c
	gcc -g3 $(INC) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make all

debug: all
	lldb ./$(NAME) padding

tests:
	@./tests	

run: all
	@./test1
