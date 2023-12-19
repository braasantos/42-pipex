#---------------VARIAVEIS-----------#
NAME = pipex
SRCS = pipex.c
HEADER = pipex.h
FT_PRINTFDIR = includes/PRINTF/libftprintf.a
LIBFTDIR = includes/LIBFT/libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
COMPILER = $(CC) $(CFLAGS)
RM = rm -f
OBJS = *.o 

all: $(NAME)

$(NAME): $(HEADER) $(OBJS)
	@echo "Created objs"
	$(MAKE) -C includes/LIBFT
	$(MAKE) -C includes/PRINTF 
	$(COMPILER) -o $(NAME) $(OBJS) includes/PRINTF/libftprintf.a \
		includes/LIBFT/libft.a -I includes/LIBFT -I includes/PRINTF   

$(OBJS): $(SRCS)
	$(COMPILER) -c $(SRCS) -I includes/LIBFT -I includes/PRINTF 

$(LIBRARIES):
	$(MAKE) -C includes/LIBFT
	$(MAKE) -C includes/PRINTF
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