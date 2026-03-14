# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42.heilbronn.d    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/14 12:31:53 by pharbst           #+#    #+#              #
#    Updated: 2026/03/14 12:48:33 by pharbst          ###   ########.fr        #
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
# CFLAGS	:=	-Wall -Werror -Wextra -Wunreachable-code -g
# CFLAGS	+=	-fsanatize=address

HEADER_DIR	:=	./include
HEADER		:=	push_swap.h

include		:=	-I $(HEADER_DIR)

VPATH		:=	src parsing algorythm stackoperations


ODIR	:=	obj
OBJS	:=	$(SRCS:%.c=$(ODIR)/%.o)

# **************************************************************************** #
# Compilation Rules
# **************************************************************************** #

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
	@$(MAKE) -s std_all

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
