
NAME = minishell
CC = cc
CFLAGS = #-Wall -Wextra -Werror
CFILES = sources/prompt_string.c \
		 sources/minishell.c \
		 sources/ft_getenv.c \
		 sources/ft_setenv.c \
		 sources/parsing/scanner.c \
		 sources/parsing/lexer_list_utils.c \
		 sources/parsing/scanner_utils.c \
		 sources/parsing/lexer.c \
		 sources/parsing/lexer_utils.c \
		 sources/parsing/error_handling.c \
		 sources/minishell_utils.c \
		 sources/parsing/traversing.c \
		 sources/parsing/parser_utils.c \
		 sources/parsing/parser.c \
		 sources/parsing/parser_list_utils.c \
		 sources/parsing/params_expander.c \
		 sources/parsing/params_expander_utils.c \
		 sources/parsing/wilcards_expander.c \
		 sources/parsing/wilcards_expander_utils.c \
		 sources/execution/executor.c \
		 sources/execution/redirections.c \
		 sources/execution/utils.c \
		 sources/execution/builtins/utils.c \
		 sources/execution/builtins/echo.c \
		 sources/execution/builtins/pwd.c \
		 sources/execution/builtins/cd.c \

SUPERLIB_DIR = ./superlib
SUPERLIB = ./superlib/superlib.a

all: $(SUPERLIB) $(NAME)

# compile the super lib
$(SUPERLIB):
	@echo "\033[0;32m[+] making superlib\033[0m"
	@$(MAKE) -C $(SUPERLIB_DIR)

$(NAME): $(CFILES)
	@echo "\033[95m[.] making minishel\033[0m"
	@$(CC) $(CFLAGS) $(CFILES) $(SUPERLIB) -lreadline -o $@

clean :
	@$(MAKE) clean -C $(SUPERLIB_DIR)
	@echo "\033[1;31m[!] deleting minishell\033[0m"
	@rm -rf $(NAME)

fclean: clean
	@$(MAKE) fclean -C $(SUPERLIB_DIR)

re : fclean all

git:
	@git add .
	@git commit -m "$m"
	@git push

.PHONY: all clean fclean re
