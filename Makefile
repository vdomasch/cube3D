# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 09:42:35 by vdomasch          #+#    #+#              #
#    Updated: 2024/11/25 13:22:21 by vdomasch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############################################################################
#									cub3D								#
#############################################################################

NAME					=		cub3D

SRCS_DIR				=		srcs

OBJS_DIR				=		.objs

HEADER_DIR			 	=		includes

DLIB					=		libft

SRCS_MANDATORY			=	init/set_elements.c									\
							init/set_map.c										\
							init/set_entities.c									\
							raycasting/raycasting.c										\
							raycasting/digital_differential_analysis.c					\
							raycasting/draw.c											\
							maps/minimap_utils.c											\

SRCS					=	$(SRCS_MANDATORY)						\
							main.c									\
							check_map.c								\
							mlx/mlx_init.c								\
							mlx/mlx.c									\
							mlx/game_loop.c								\
							maps/minimap.c									\
							free.c

NAME_BONUS			=	cub3D_bonus

ifeq ($(BONUS),true)
	
SRCS				=	$(SRCS_MANDATORY)			\
						bonus/main_bonus.c			\
						bonus/check_map_bonus.c		\
						bonus/mlx_bonus.c			\
						bonus/mlx_init_bonus.c		\
						bonus/game_loop_bonus.c		\
						bonus/door_bonus.c			\
						bonus/minimap_bonus.c		\
						bonus/big_map_bonus.c		\
						bonus/fps_bonus.c			\
						bonus/free_bonus.c

endif						

OBJS					=		$(SRCS:%.c=$(OBJS_DIR)/%.o)

HEADERS					=		$(HEADER_DIR)/$(NAME).h

CC						=		cc

FLAGS					=		-Wall -Werror -Wextra

DFLAGS					=		-fsanitize=address -g3

#############################################################################
#									MINILIBX								#
#############################################################################

MLX			:=	libmlx.a

MLX_D		:=	minilibx-linux/

MLX_F		:= -L ./minilibx-linux -lmlx -lXext -lX11 -lm

MLX_A		:=	$(addprefix $(MLX_D), $(MLX))

#############################################################################
#									DEBUG									#
#############################################################################

ifeq ($(DEBUG),true)
		FLAGS = -Wall -Werror -Wextra $(DFLAGS)
endif

#############################################################################
#									RULES									#
#############################################################################

all:				lib $(OBJS_DIR) $(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c $(HEADERS)
						$(CC) $(FLAGS) -I/usr/include -Iminilibx-linux -c $< -o $@

$(NAME):			$(OBJS_DIR) $(OBJS) $(HEADERS) $(DLIB)/libft.a Makefile $(MLX_A) 
						$(CC) $(FLAGS) -lm $(OBJS) $(DLIB)/libft.a $(MLX_A) $(MLX_F) -o $(NAME)

$(NAME_BONUS):			$(OBJS_DIR) $(OBJS) $(HEADERS) $(DLIB)/libft.a Makefile $(MLX_A) 
						$(CC) $(FLAGS) -lm $(OBJS) $(DLIB)/libft.a $(MLX_A) $(MLX_F) -o $(NAME_BONUS)

$(OBJS_DIR):
						mkdir -p $(OBJS_DIR)
						mkdir -p $(OBJS_DIR)/init
						mkdir -p $(OBJS_DIR)/mlx
						mkdir -p $(OBJS_DIR)/raycasting
						mkdir -p $(OBJS_DIR)/maps
						mkdir -p $(OBJS_DIR)/bonus

lib:
						$(MAKE) -s -C $(MLX_D)
						$(MAKE) -s -C $(DLIB)

clean:
						rm -rf $(OBJS_DIR)
						$(MAKE) -s clean -C $(DLIB)
						$(MAKE) -s clean -C $(MLX_D)

fclean:
						$(MAKE) clean
						rm -rf $(NAME)
						rm -rf $(NAME_BONUS)
						$(MAKE) -s fclean -C $(DLIB)

re:
						$(MAKE) fclean all

debug:
						@$(MAKE) fclean all DEBUG=true

bonus:								
						$(MAKE) lib $(NAME_BONUS) BONUS=true

.PHONY: all clean fclean re lib debug