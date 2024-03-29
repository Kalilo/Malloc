# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggroener <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/28 11:16:22 by ggroener          #+#    #+#              #
#    Updated: 2016/12/04 17:14:27 by khansman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = malloc.so

ifndef $(HOSTTYPE)
HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif

ifeq ($(shell uname -s), Darwin)
SYS = OSX
else
SYS = UNKNOWN
endif

SYSNAME_PRE = libft_malloc_

SYSNAME_EXT = .so

SYSNAME = $(addprefix $(addprefix $(SYSNAME_PRE), $(HOSTTYPE)), $(SYSNAME_EXT))

CFLAGS =	-Wall -Wextra -Werror -fPIC -O3

CFLAGS2 =	-shared -Wall -Wextra -Werror -O3

CC = gcc

INCLUDES_PATH = includes/

SRCS_PATH = srcs/

SRCS_NAME = calloc.c						\
			error_quit.c					\
			find_block.c					\
			free.c							\
			ft_bzero.c						\
			ft_print_hex_l.c				\
			ft_memmove.c					\
			ft_putchar.c					\
			ft_putendl.c					\
			ft_putnbr.c						\
			ft_putstr.c						\
			init.c							\
			malloc.c						\
			pages.c							\
			print.c							\
			realloc.c						\
			realloc_large_block.c			\
			realloc_small_block.c			\
			realloc_tiny_block.c			\
			scan_small_block.c				\
			scan_tiny_block.c				\
			show_alloc_mem.c				\
			zones.c							\

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = objs/

OBJS_NAME = $(SRCS_NAME:.c=.o)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

#uncomment these to work on Mac and comment to work on Linux.
LIBRARY =

INCLUDES = -I includes/

#uncomment these to work on Linux and comment to work on Mac.
#LIBRARY = -L /usr/X11/lib -lmlx -lX11 -lm -lXext -L libft/ -lft
 
#INCLUDES = -I includes/ -I libft/includes -I /usr/X11/include

HEADER = 	$(INCLUDES_PATH)malloc.h		\

all: qme odir $(NAME)

define colourecho
	@tput setaf 14
	@echo $1
	@tput sgr0
endef

define colourecho2
	@tput setaf 2
	@echo $1
	@tput sgr0
endef

$(SYSNAME): $(NAME)

$(NAME): $(OBJS)
	@Make compile

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(call colourecho, " - Compiling $<")
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $< -I$(INCLUDES_PATH)
	@$(call colourecho, "Compiling Done!")

compile: qme odir $(OBJS)
	@$(call colourecho, "Compiling $(SYSNAME)")
	@ar -rc $(SYSNAME) $(OBJS)
	@ranlib $(SYSNAME)
	@$(call colourecho, "Done Compiling!")
	@ln -f -s $(SYSNAME) $(NAME)

odir:
	@mkdir -p $(OBJS_PATH)

clean:
	@$(call colourecho, " - Clearing object files")
	@rm -f $(OBJS)
	@$(call colourecho, "clean done!")

fclean: clean
	@$(call colourecho, "Clearing executable files")
	@rm -f $(NAME) $(SYSNAME)
	@$(call colourecho, "fclean done")

re: fclean all
	@$(call colourecho, "re Done!")

format: norme me

norme: norm

norm:
	@clear
	@$(call colourecho2, "Norminette:")
	@norminette $(SRCS)
	@norminette $(HEADER)

fnorm: fnorme

fnorme:
	@clear
	@$(call colourecho2, "Norminette:")
	@find ./srcs -name "*.c" -maxdepth 1 -type f -exec norminette  {} \;
	@find ./includes -name "*.h" -maxdepth 1 -type f -exec norminette  {} \;

submodule:
	@$(call colourecho, "Checking Submodules...")
	@if [ ! -d libft/includes ]; then \
		git submodule init libft; \
		git submodule update; \
	fi;
	@$(call colourecho, "done checking submodules")

test:
	@make
	@clear
	@$(call colourecho2, "\nTest Main 00:")
	@gcc ./malloc.so testing/test_main00.c && ./a.out
	@$(call colourecho2, "\nTest Main 01:")
	@gcc ./malloc.so testing/test_main01.c && ./a.out

qme:
	@if [ ! -f author ]; then \
		whoami > author; \
	fi
	
me: qme
	cat -e author

.PHONY: clean fclean re odir
