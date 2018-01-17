NAME = ft_ls
#LD = -Llibft -lft
LD = libft/libft.a libft/printf/build/libftprintf.a
INC = $(addprefix -I, . libft libft/list libft/printf libft/printf/build/includes)
FLAGS = $(INC) $(LD)
MAIN = main.c utils.c mklist.c process.c list_utils.c
PRINT = $(addprefix padding/, main.c utils.c colors.c print.c)
SRCS = $(MAIN) $(PRINT)
OBJS = $(SRCS:%.c=objs/%.o)

vpath %.c srcs

all: $(OBJS)
	@make -C libft
	gcc -g3 -lm -lncurses $(LD) $^ -o $(NAME)

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
