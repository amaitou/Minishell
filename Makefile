
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFILES = prompt_string.c \
		 minishell.c \
		 sources/lexer/tokenizer.c \
		 sources/lexer/utils.c \
		 sources/lexer/params_expansion.c \
		 sources/lexer/wildcards_expansion.c

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