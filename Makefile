NAME = pipex
SRCS = pipex.c pipex_utils.c pipex_utils_2.c pipex_utils_3.c
HEADER = pipex.h
LIBFTDIR = includes/LIBFT/libft.a
PRINTFDIR = includes/PRINTF/libftprintf.a
CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3
COMPILER = $(CC) $(CFLAGS)
RM = rm -f
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTDIR) $(PRINTFDIR) $(HEADER)
	@echo "Created objs"
	$(COMPILER) $(OBJS) $(LIBFTDIR) $(PRINTFDIR) -I includes/LIBFT -I includes/PRINTF -o $(NAME)

$(LIBFTDIR):
	$(MAKE) -C includes/LIBFT

$(PRINTFDIR):
	$(MAKE) -C includes/PRINTF

%.o: %.c
	$(COMPILER) -I includes/LIBFT -I includes/PRINTF -c $< -o $@ 

debug:
	cc $(CFLAGS) -g -I includes/LIBFT -I includes/PRINTF *.c includes/LIBFT/*.c

clean:
	$(RM) $(OBJS)
	$(MAKE) -C includes/LIBFT clean
	$(MAKE) -C includes/PRINTF clean

fclean: clean
	@echo "Deleted objs"
	$(RM) $(NAME)
	$(MAKE) -C includes/LIBFT fclean
	$(MAKE) -C includes/PRINTF fclean

re: fclean all

.PHONY: all clean fclean re
