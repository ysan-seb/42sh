# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/02 21:00:40 by mdescamp          #+#    #+#              #
#    Updated: 2017/12/08 11:19:30 by pguillie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 42sh
CC		= gcc
FLAGS	= -Wall -Werror -Wextra
INCPATH	= includes/
HEADERS	= $(addprefix $(INCPATH), shell.h)
LIBPATH	= libft/
LIB		= $(LIBPATH)libft.a
TERMCAP	= -ltermcap

SOURCES	:= $(shell find src | grep "\.c" | grep -v "\.c.")
NB		:= $(shell find src | grep "\.c" | grep -v "\.c." | wc -l\
		| rev | cut -f 1 -d ' ' | rev)

OBJECTS	= $(SOURCES:src/%.c=obj/%.o)

RED		= \033[31m
GREEN	= \033[32m
BLUE	= \033[34m
WHITE	= \033[37m
EOC		= \033[0m

.PHONY: all clean nclean fclean re

all: $(NAME)

$(NAME): obj $(LIB) $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIB) $(TERMCAP)
	@ echo "$(GREEN)[$@]: binary successfully created !$(EOC)"

obj/%.o: src/%.c $(HEADERS) Makefile
	$(eval FILE=$(shell echo $$(($(FILE) + 1))))
	$(eval PERCENT=$(shell echo $$(($(FILE) * 100 / $(NB)))))
	@ echo "[$(NAME)]: $(PERCENT)% ($(FILE)/$(NB))\r\c"
	$(CC) $(FLAGS) -I $(INCPATH) -o $@ -c $<

obj:
	mkdir -p ./obj/builtins
	mkdir -p ./obj/execution
	mkdir -p ./obj/expansion
	mkdir -p ./obj/hash
	mkdir -p ./obj/hci/completion
	mkdir -p ./obj/hci/conversions
	mkdir -p ./obj/hci/cur_motion
	mkdir -p ./obj/hci/edition
	mkdir -p ./obj/hci/history
	mkdir -p ./obj/hci/lexer
	mkdir -p ./obj/hci/prompt
	mkdir -p ./obj/hist_exp
	mkdir -p ./obj/initialization
	mkdir -p ./obj/parser
	mkdir -p ./obj/signals
	mkdir -p ./obj/var
	@ echo "$(BLUE)[$(NAME)]: objects directory created$(EOC)"

$(LIB):
	make -C $(LIBPATH)

clean:
	make -C $(LIBPATH) clean
	rm -rf obj
	@ echo "$(RED)[$(NAME)]: objects directory deleted$(EOC)"

nclean:
	rm -rf $(NAME)
	@ echo "$(RED)[$(NAME)]: binary file deleted$(EOC)"

fclean: clean nclean
	make -C $(LIBPATH) nclean

re: fclean all
