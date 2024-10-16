NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE = -lreadline
#CFLAGS += -fsanitize=address -g3

SRC = \
    builtin_cmd/export/export.c \
    builtin_cmd/export/check_functions.c \
    builtin_cmd/export/check_functions_1.c \
    builtin_cmd/export/export_utils_1.c \
    builtin_cmd/export/export_utils_0.c \
    builtin_cmd/export/export_utils_2.c \
    builtin_cmd/cd/ft_cd.c \
    builtin_cmd/cd/ft_cd_utils_0.c \
    builtin_cmd/cd/ft_cd_utils_1.c \
    builtin_cmd/exit/ft_exit.c \
    builtin_cmd/exit/ft_exit_utils.c \
	builtin_cmd/ft_echo.c \
	builtin_cmd/ft_env.c \
	builtin_cmd/ft_pwd.c \
	builtin_cmd/ft_unset.c\
    executable_cmd/executable_cmd.c \
    executable_cmd/child_process_1.c \
    executable_cmd/child_process_0.c \
	execution_utils/execution_utils_0.c \
	execution_utils/execution_utils_1.c \
	execution_utils/execution_utils_2.c \
	execution_utils/execution_utils_3.c \
	execution_utils/execution_utils_4.c \
	execution_utils/execution_utils_5.c \
	link_parsing_execution/manage_cmd.c execution_utils/ft_strtrim.c \
	link_parsing_execution/manage_files_0.c \
	link_parsing_execution/manage_files_1.c \
	link_parsing_execution/manage_files_2.c \
	link_parsing_execution/manage_pipes_0.c	\
	link_parsing_execution/execution.c	\
	optimize_handle_errors/handle_exit_errors.c	\
	optimize_handle_errors/handle_file_descriptors.c	\
	parsing/parsing.c parsing/display.c parsing/utils.c \
	parsing/clean_up.c parsing/ft_split_quotes.c \
	parsing/set_up_for_execution.c parsing/expand_cmd.c \
	parsing/ft_lstadd_line_splited.c parsing/ft_lstadd_redirection.c \
	parsing/expand.c parsing/redirection.c parsing/ft_strlcat.c \
	parsing/ft_strlcpy.c parsing/char_utils.c parsing/clean_up_ptr.c \
	parsing/counting_utils.c parsing/expand_redirection.c \
	parsing/ft_split_with_white_spaces.c parsing/ft_strjoin_pro.c \
	parsing/ft_strndup.c parsing/search_in_env.c \
	parsing/something_is_wrong.c parsing/norminette.c parsing/utils2.c \
	main_utils.c parsing/rm_quotes_redirection.c \
	main.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(READLINE) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME) 

re: fclean all

.PHONY: all fclean re clean bonus
