# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 10:18:08 by vdomasch          #+#    #+#              #
#    Updated: 2024/09/03 11:36:40 by vdomasch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############################################################################
#									VARIABLE								#
#############################################################################

NAME				=	test

HEADER_DIR			=	.
SRCS_DIR			=	./
OBJS_DIR			=	.objs

HEADERS				=	test.h

SRCS				=	main.c
					
OBJS				=	$(SRCS:%.c=$(OBJS_DIR)/%.o)

LIB_D				=	../../libft

#############################################################################
#									COMPILATION								#
#############################################################################

CC					=	cc
FLAGS				=	-Wall -Werror -Wextra -g3

#############################################################################
#									MINILIBX								#
#############################################################################

MLX			:=	libmlx.a

MLX_D		:=	../../minilibx-linux/

MLX_F	:= -L ../../minilibx-linux -lmlx -lXext -lX11

MLX_A		:=	$(addprefix $(MLX_D), $(MLX))

#############################################################################
#										RULES								#
#############################################################################

all					:	lib $(NAME) 

lib				:
							@$(MAKE) -C $(MLX_D)
							@$(MAKE) -C $(LIB_D)

$(NAME)				:	$(OBJS_DIR) $(OBJS) $(HEADERS) $(LIB_D)/libft.a $(MLX_A)
							$(CC) $(FLAGS) $(OBJS) $(LIB_D)/libft.a $(MLX_A) $(MLX_F) -o $(NAME)
							
$(OBJS_DIR)/%.o		:	$(SRCS_DIR)/%.c $(HEADERS)
							$(CC) $(FLAGS) -I/usr/include -Iminilibx-linux -c $< -o $@

$(OBJS_DIR)			:
							mkdir -p $(OBJS_DIR)

#############################################################################
#									COMMANDS								#
#############################################################################

clean				:
							rm -rf $(OBJS_DIR)

fclean				:
							$(MAKE) clean
							rm -rf $(NAME)


fclean_bonus		:		
							rm -rf $(NAME)

re					:
							$(MAKE) fclean all

bonus				:
							@$(MAKE) all BONUS=true
							
.PHONY: all clean fclean re lib bonus fclean_bonus