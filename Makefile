NAME := ft_ls
SRCS := main.c ft_ls.c

all: $(NAME)

$(NAME):
	gcc -g3 $(SRCS) -o $(NAME)

fclean:
	rm -rf $(NAME)

re: fclean
	make all

run: re
	@./test1
