NAME = ft_ls
#LD = -Llibft -lft
LD = libft/libft.a
INC = -I libft/list -I libft -I .
FLAGS = $(INC) $(LD)
SRCS = main.c utils.c print.c mklist.c process.c list_utils.c padding/main.c padding/utils.c
OBJS = $(SRCS:%.c=objs/%.o)

vpath %.c srcs

all: $(OBJS)
	@make -C libft
	gcc -g3  -lm -lncurses $(LD) $^ -o $(NAME)

objs/%.o:%.c
	gcc -g3 $(INC) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make all

debug: all
	lldb ./$(NAME) test

tests: all
	@cd Unit_tests && ./tests	

run: all
	@./ft_ls -r
