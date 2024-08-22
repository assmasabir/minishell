NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -fsanitize=address -g3

SRC = \
    built_in_cmd/export/export_0.c \
    built_in_cmd/export/check_functions.c \
    built_in_cmd/export/export_1.c \
    built_in_cmd/export/export_utils.c \
    built_in_cmd/builtin_cmd_1.c \
    built_in_cmd/builtin_cmd_2.c \
    executable_cmd/executable.c \
	execution_utils/execution_utils_0.c \
	execution_utils/execution_utils_1.c \
	execution_utils/execution_utils_2.c \
	link_parsing_execution/manage_cmd.c \
	link_parsing_execution/execution.c \
    link_parsing_execution/get_next_line/get_next_line.c \
    link_parsing_execution/get_next_line/get_next_line_utils.c \
	link_parsing_execution/manage_pipes.c \
	main.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME) 

re: fclean all

.PHONY: all fclean re clean bonus
