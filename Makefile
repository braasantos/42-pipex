NAME = pipex
NAME_BONUS = pipex_bonus
HEAD = main.c
SRCS = pipex.c pipex_execute.c pipex_utils.c pipex_files.c
SRCS_BONUS = main_bonus.c
HEADER = pipex.h
LIBFTDIR = includes/LIBFT/libft.a
PRINTFDIR = includes/PRINTF/libftprintf.a
CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3
COMPILER = $(CC) $(CFLAGS)
RM = rm -f
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
MAIN = $(HEAD:.c=.o)

all: $(NAME)
bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(MAIN) $(LIBFTDIR) $(PRINTFDIR) $(HEADER)
	@echo "Created objs"
	$(COMPILER) $(OBJS) $(MAIN) $(LIBFTDIR) $(PRINTFDIR) -I includes/LIBFT -I includes/PRINTF -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS) $(OBJS) $(LIBFTDIR) $(PRINTFDIR) $(HEADER)
	@echo "Created objs_bonus"
	$(COMPILER) $(OBJS_BONUS) $(OBJS) $(LIBFTDIR) $(PRINTFDIR) -I includes/LIBFT -I includes/PRINTF -o $(NAME_BONUS)

$(LIBFTDIR):
	$(MAKE) -C includes/LIBFT

$(PRINTFDIR):
	$(MAKE) -C includes/PRINTF

%.o: %.c
	$(COMPILER) -I includes/LIBFT -I includes/PRINTF -c $< -o $@ 

debug:
	cc $(CFLAGS) -g -I includes/LIBFT -I includes/PRINTF *.c includes/LIBFT/*.c

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) $(MAIN)
	$(MAKE) -C includes/LIBFT clean
	$(MAKE) -C includes/PRINTF clean

fclean: clean
	@echo "Deleted objs"
	$(RM) $(NAME) $(NAME_BONUS)
	$(MAKE) -C includes/LIBFT fclean
	$(MAKE) -C includes/PRINTF fclean

re: fclean all

.PHONY: all clean fclean re bonus

