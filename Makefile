# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/03 16:20:41 by clouden           #+#    #+#              #
#    Updated: 2025/09/22 13:32:22 by clouden          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED		=	\033[0;31m
GREEN   =	\033[0;32m
RESET   =	\033[0m  
YELLOW  =	\033[1;33m
BLUE    =	\033[0;34m

# Project Variables
CC		= 	cc
CFLAGS 	= 	-Wall -Wextra -Werror -I./libft -I./minilibx -g3
LIBMLX	=	./minilibx-linux
LIBMLXA =	./minilibx-linux/libmlx.a
NAME	=	fractol
BN_NAME =	fractol_bonus

SRCS 	=	main.c \
			error_clean.c \
			plot_image.c \
			event_wrappers.c \
			event_shift.c \
			event_zoom.c \
			math_utils.c \
			init.c \
			tables.c

BN_SRCS 	=	main.c \
			error_clean.c \
			plot_image.c \
			event_wrappers.c \
			event_shift.c \
			event_zoom_bonus.c \
			math_utils.c \
			init.c \
			tables.c


OBJS	=	$(SRCS:%.c=%.o)

BN_OBJS	=	$(BN_SRCS:%.c=%.o)

LIBFT_DIR	=	libft/
LIBFT		=	$(LIBFT_DIR)libft.a

all:$(NAME)

$(NAME):$(OBJS) $(LIBFT)
	@echo "$(BLUE)[FRACTOL]$(RESET) $< → $@"
	@$(CC) $(CFLAGS) $^ $(LIBMLXA) -o $@ -lX11 -lXext -lm

bonus:$(BN_NAME) 

$(BN_NAME):$(BN_OBJS) $(LIBFT)
	@echo "$(BLUE)[BONUS_FRACTOL]$(RESET) $< → $@"
	@$(CC) $(CFLAGS) $^ $(LIBMLXA) -o $@ -lX11 -lXext -lm

$(LIBMLXA) : $(LIBMLX)
	@make -C minilibx-linux > /dev/null 2>&1

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all --no-print-directory

%.o: %.c
	@printf "$(BLUE)[COMPILING]$(RESET) %-21s → %s\n" $< $@
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)"
	@echo "+---------------------------+"
	@echo "|      CLEANING OBJECTS     |"
	@echo "+---------------------------+"
	@rm -rf *.o $(OBJS) $(BN_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@echo "$(YELLOW)"
	@echo "+---------------------------+"
	@echo "|   REMOVING EXECUTABLES    |"
	@echo "+---------------------------+"
	@rm -f $(NAME) $(BN_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(RESET)"
	@echo "...now THAT'S effin' clean!\n"

re: fclean all

.PHONY: re all clean fclean

