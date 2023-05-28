
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFILES = sources/prompt_string.c \
		 sources/minishell.c \
		 sources/free_pointers.c \
		 sources/parser/tokenizer.c \
		 sources/parser/utils.c \
		 sources/parser/params_expander.c \
		 sources/parser/params_expander_utils.c \
		 sources/parser/wildcards_expander.c \
		 sources/parser/wildcards_expander_utils.c \
		 sources/builtins/init_env.c \
		 sources/builtins/ft_getenv.c \
		 sources/parser/quotes_removal.c \
		 sources/parser/final_tokens.c

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
