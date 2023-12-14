#---------------VARIAVEIS-----------#
NAME = pipex
SRCS = pipex.c
HEADER = pipex.h
CC = cc
CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3
COMPILER = $(CC) $(CFLAGS)
RM = rm -f
OBJS = *.o 

all: $(NAME)

$(NAME): $(HEADER) $(OBJS)
	@echo "Created objs"
	$(COMPILER) -o $(NAME) $(OBJS)

$(OBJS): $(SRCS)
	$(COMPILER) -c $(SRCS)
# cleans the object files
clean:
	$(RM) $(OBJS) $(DEPS)

# cleans the object files and the executable
fclean: clean
	@echo "Deleted objs"
	$(RM) $(NAME)

# cleans and rebuilds the project
re: fclean all

.PHONY: all clean fclean re
.SILENT: