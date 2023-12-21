NAME = pipex
SRCS = pipex.c pipex_utils.c
HEADER = pipex.h
LIBFTDIR = includes/LIBFT/libft.a
PRINTFDIR = includes/PRINTF/libftprintf.a
CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3
COMPILER = $(CC) $(CFLAGS)
RM = rm -f
OBJS = *.o 

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTDIR) $(PRINTFDIR) $(HEADER)
	@echo "Created objs"
	$(COMPILER) -o $(NAME) $(OBJS) $(LIBFTDIR) $(PRINTFDIR) -I includes/LIBFT -I includes/PRINTF

$(LIBFTDIR):
	$(MAKE) -C includes/LIBFT

$(PRINTFDIR):
	$(MAKE) -C includes/PRINTF

$(OBJS): $(SRCS)
	$(COMPILER) -c $(SRCS) -I includes/LIBFT -I includes/PRINTF

# cleans the object files
clean:
	$(RM) $(OBJS)
	$(MAKE) -C includes/LIBFT clean
	$(MAKE) -C includes/PRINTF clean

# cleans the object files and the executable
fclean: clean
	@echo "Deleted objs"
	$(RM) $(NAME)
	$(MAKE) -C includes/LIBFT fclean
	$(MAKE) -C includes/PRINTF fclean

# cleans and rebuilds the project
re: fclean all

.PHONY: all clean fclean re
.SILENT:
