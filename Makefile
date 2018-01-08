NAME = ft_ls
#LD = -Llibft -lft
LD = libft/*.o libft/list/*.o
INC = -I libft/list -I libft -I .
FLAGS = $(INC) $(LD) 
SRCS = main.c ft_ls.c read_dir.c print.c mklist.c print2.c
OBJS = $(SRCS:%.c=objs/%.o)

vpath %.c srcs

all: $(OBJS)
	gcc -g3 $(LD) $^ -o $(NAME)

$(NAME): $(OBJS)
	@make -C libft

objs/%.o:%.c
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
	@.test/tests	

run: all
	@./test/test1
