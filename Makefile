# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/25 13:02:54 by wbraeckm          #+#    #+#              #
#    Updated: 2019/01/20 16:06:04 by wbraeckm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = gcc
FLAGS = -O3 -Wall -Wextra -Werror #-fsanitize=address
INCLUDES = ./includes/
SRCSFOLDER = ./srcs/
OBJFOLDER = ./obj/
LIBFOLDER = ./libft/
LIBINCLUDES = ./libft/includes/
LIBFT = $(LIBFOLDER)libft.a

ITEMS = $(shell find srcs -type f | grep -E ".c$$" | sed 's/srcs//g')
SRCS = $(addprefix $(SRCSFOLDER), $(ITEMS))
OBJ = $(addprefix $(OBJFOLDER), $(ITEMS:.c=.o))
SRCSUBS = $(shell find ./srcs -type d)
OBJSUBS = $(SRCSUBS:./srcs%=./obj%)
LONGEST = $(shell echo $(notdir $(SRCS)) | tr " " "\n" | \
	awk ' { if ( length > x ) { x = length; y = $$0 } }END{ print y }' | wc -c)

ccblue = "\33[0;34m"
ccred = "\033[0;91m"
ccgreen = "\033[0;92m"
ccgreenhard = "\033[0;32m"
cccyan = "\033[0;96m"
ccreset = "\033[0;0m"
cclightgray = "\033[0;37m"

all: lib $(NAME)

$(OBJFOLDER)/%.o:$(SRCSFOLDER)/%.c includes/lem_in.h Makefile
	@printf $(ccblue)
	@printf "Compiling %-$(LONGEST)s" $(notdir $<)
	@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES) -I$(LIBINCLUDES)
	@printf $(cclightgray)[$(ccgreenhard)√$(cclightgray)]$(ccreset)
	@printf "\r"

$(OBJSUBS):
	@mkdir $@

lib:
	@make -C $(LIBFOLDER)

$(NAME): $(OBJSUBS) $(OBJ) Makefile
	@printf $(cccyan)
	@printf "Compiling $(NAME) "
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) -I$(INCLUDES) \
-I$(LIBINCLUDES) $(LIBFT)
	@printf $(cclightgray)[$(ccgreenhard)√$(cclightgray)]$(ccreset)
	@printf "                                                     \n"

clean:
	@printf $(ccred)
	rm -rf obj/
	@make -C $(LIBFOLDER) clean
	@printf $(ccreset)

fclean: clean
	@printf $(ccred)
	rm -rf $(NAME_PUSHSWAP) $(NAME_CHECKER)
	@make -C $(LIBFOLDER) fclean
	@printf $(ccreset)

re: fclean all

norm:
	@norminette $(SRCSFOLDER) $(INCLUDES)

.PHONY: norm clean fclean re
