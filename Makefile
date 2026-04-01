# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/14 12:31:53 by pharbst           #+#    #+#              #
#    Updated: 2026/03/17 05:04:36 by pharbst          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
# Operating System tracking
# **************************************************************************** #
UNAME		=	$(shell uname)
OS			=	$(shell cat /etc/os-release | grep -e NAME | cut -d= -f2 | tr -d '"')
OS_LIKE		=	$(shell cat /etc/os-release | grep ID_LIKE | cut -d= -f2)


# **************************************************************************** #
# Variables
# **************************************************************************** #

NAME	:=	push_swap
BNAME	:=	checker

CC		:=	cc
CFLAGS	:=	-Wall -Werror -Wextra
CFLAGS	+=	-g
# DEBUG_CFLAGS	+=	-fsanatize=address

HEADER_DIR	:=	./include
HEADER		:=	push_swap.h

INCLUDE		:=	-I $(HEADER_DIR)

VPATH		:=	src src/parsing src/algorythm src/stackoperations

SRCS		:=	push_swap.c \
				parser_helper.c \
				reduce_normalize.c \
				stack_creation.c \
				push.c \
				rotate.c \
				rev_rotate.c \
				swap.c \
				midpoint.c

ODIR	:=	obj
OBJS	:=	$(SRCS:%.c=$(ODIR)/%.o)

# **************************************************************************** #
# Compilation Rules
# **************************************************************************** #

# test:
# 	$(CC) $(DEBUG_CFLAGS) $(INCLUDE) src/parsing/*.c -o app
# 	./app $(ARGS)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)


$(ODIR)/%.o: %.c | $(ODIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(ODIR):
	@mkdir -p $@

clean:
	@$(MAKE) -s proname_header
	@$(MAKE) -s std_clean

std_clean:
	@printf "%-60s$(RESET)" "$(FPurple)Cleaning up ..."
	@$(RM) -rf $(ODIR)
	@printf "$(FGreen)$(TICKBOX)\n$(RESET)"

fclean:	libft
	@$(MAKE) -s proname_header
	@$(MAKE) -s cleanator

cleanator:
	@printf "%-60s$(RESET)" "$(FPurple)FCleaning up ..."
	@$(RM) -rf $(ODIR)
	@$(RM) -rf $(NAME)
	@printf "$(FGreen)$(TICKBOX)\n$(RESET)"

re:
	@$(MAKE) -s proname_header
	@$(MAKE) -s cleanator
	@$(MAKE) -s all

# **************************************************************************** #
# Header Rules                                                                 #
# **************************************************************************** #

proname_header:
	@printf "$(FCyan)╔══════════════════════════════════════════════════════╗$(RESET)\n\
$(FCyan)║$(FPurple)  _____           _        _____                      $(FCyan)║\n\
$(FCyan)║$(FPurple) |  __ \\         | |      / ____|                     $(FCyan)║\n\
$(FCyan)║$(FPurple) | |__) |   _ ___| |__   | (_____      ____ _ _ __    $(FCyan)║\n\
$(FCyan)║$(FPurple) |  ___/ | | / __| \'_ \\   \\___ \\ \\ /\\ / / _\` | \'_ \\   $(FCyan)║\n\
$(FCyan)║$(FPurple) | |   | |_| \\__ \\ | | |  ____) \\ V  V / (_| | |_) |  $(FCyan)║\n\
$(FCyan)║$(FPurple) |_|    \\__,_|___/_| |_| |_____/ \\_/\\_/ \\__,_| .__/   $(FCyan)║\n\
$(FCyan)║$(FPurple)                     ______                  | |      $(FCyan)║\n\
$(FCyan)║$(FPurple)                    |______|                 |_|      $(FCyan)║\n\
$(FCyan)╚══════════════════════════════════════════════════════╝\n$(RESET)"
