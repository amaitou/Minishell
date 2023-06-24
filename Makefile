
NAME = minishell
CC = cc
CFLAGS =  -I /Users/amait-ou/goinfre/homebrew/opt/readline/include -Wall -Wextra -Werror
CFILES = sources/prompt_string.c \
		 sources/minishell.c \
		 sources/ft_getenv.c \
		 sources/ft_setenv.c \
		 sources/parse_and_execute.c \
		 sources/parsing/scanner.c \
		 sources/parsing/scanner_utils.c \
		 sources/parsing/lexer.c \
		 sources/parsing/lexer_list.c \
		 sources/parsing/lexer_utils.c \
		 sources/parsing/lexer_utils_2.c \
		 sources/parsing/minishell_leaks.c \
		 sources/parsing/minishell_leaks_utils.c \
		 sources/parsing/error_handling.c \
		 sources/parsing/parser.c \
		 sources/parsing/parser_list.c \
		 sources/parsing/parser_utils_2.c \
		 sources/parsing/parser_utils.c \
		 sources/parsing/params_expander.c \
		 sources/parsing/params_expander_utils.c \
		 sources/parsing/wildcards_expander.c \
		 sources/parsing/wildcards_expander_utils.c \
		 sources/execution/executor.c \
		 sources/execution/redirections.c \
		 sources/execution/utils.c \
		 sources/execution/utils_2.c \
		 sources/execution/builtins/utils.c \
		 sources/execution/builtins/echo.c \
		 sources/execution/builtins/pwd.c \
		 sources/execution/builtins/cd.c \
		 sources/execution/builtins/env.c \
		 sources/execution/builtins/export.c \
		 sources/execution/builtins/unset.c \
		 sources/execution/builtins/exit.c \
		 sources/minishell_utils.c \
		 sources/parsing/ambiguous_error.c \
		 sources/parsing/error_handling_utils.c \
		 sources/split_expanded_tokens.c

DEPS = includes/minishell.h

SOURCES = $(CFILES:.c=.o)

SUPERLIB_DIR = ./superlib
SUPERLIB = ./superlib/superlib.a

all: $(SUPERLIB) $(DEPS) $(NAME) 

# compile the super lib

$(SUPERLIB):
	@echo "\033[0;32m[+] Making Superlib\033[0m"
	@$(MAKE) -C $(SUPERLIB_DIR)

# compiling minishell

$(NAME): $(SOURCES) $(DEPS)
	@echo "\033[95m[.] Making Minishel\033[0m"
	@$(CC) $(CFLAGS) $(SOURCES) $(SUPERLIB) -lreadline -L /Users/amait-ou/goinfre/homebrew/opt/readline/lib -o $@

./sources/execution/%.o: ./sources/execution/%.c $(DEPS)
	@echo "\033[0;33m[*] Compiling $?\033[0m"
	@$(CC) $(CFLAGS) $< -c -o $@

./sources/execution/builtins/%.o: ./sources/execution/builtins/%.c $(DEPS)
	@echo "\033[0;33m[*] Compiling $?\033[0m"
	@$(CC) $(CFLAGS) $< -c -o $@

./sources/parsing/%.o: ./sources/parsing/%.c $(DEPS)
	@echo "\033[0;33m[*] Compiling $?\033[0m"
	@$(CC) $(CFLAGS) $< -c -o $@

./sources/%.o: ./sources/%.c $(DEPS)
	@echo "\033[0;33m[*] Compiling $?\033[0m"
	@$(CC) $(CFLAGS) $< -c -o $@

clean :
	@$(MAKE) clean -C $(SUPERLIB_DIR)
	@@echo "\033[1;31m[!] Deleting Object Files\033[0m"
	@rm -rf	$(SOURCES)

fclean: clean
	@$(MAKE) fclean -C $(SUPERLIB_DIR)
	@echo "\033[1;31m[!] Deleting Minishell\033[0m"
	@rm -rf $(NAME)

re : fclean all

run: all
	@clear && ./minishell

git:
	@git add .
	@git commit -m "$m"
	@git push

.PHONY: all clean fclean re
