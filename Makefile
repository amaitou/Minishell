
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFILES = command_prompt.c \
		 minishell.c \
		 sources/lexer/split_command.c \
		 sources/lexer/lexer_utils.c

SUPERLIB_DIR = ./superlib
SUPERLIB = ./superlib/superlib.a

all: $(SUPERLIB) $(NAME)

# compile the super lib
$(SUPERLIB):
	@echo "\033[0;32m[+] making superlib\033[0m"
	@$(MAKE) -C $(SUPERLIB_DIR)

$(NAME): $(CFILES)
	@$(CC) $(CFLAGS) $(CFILES) $(SUPERLIB) -lreadline -o $@

clean :
	@$(MAKE) clean -C $(SUPERLIB_DIR)
	@echo "\033[1;31m[!] deleting minishell\033[0m"
	@rm -rf $(NAME)

fclean: clean
	@$(MAKE) fclean -C $(SUPERLIB_DIR)

re : fclean all

.PHONY: all clean fclean re