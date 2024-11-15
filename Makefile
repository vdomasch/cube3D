# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 09:42:35 by vdomasch          #+#    #+#              #
#    Updated: 2024/11/15 13:31:01 by vdomasch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############################################################################
#									cub3D								#
#############################################################################

NAME						=		cub3D

SRCS_DIR					=		srcs

OBJS_DIR					=		.objs

HEADER_DIR				 	=		includes

DLIB						=		libft

SRCS_MANDATORY				=		main.c											\
									check_map.c										\
									init/set_elements.c									\
									init/set_map.c										\
									init/set_entities.c									\
									mlx/mlx_init.c											\
									raycasting/raycasting.c										\
									raycasting/digital_differential_analysis.c					\
									raycasting/draw.c											\
									maps/big_map.c													\
									maps/minimap.c													\
									maps/minimap_utils.c											\
									maps/door.c														\
									free.c

SRCS					=	$(SRCS_MANDATORY)						\
							mlx/game_loop.c				\
							mlx/mlx.c

ifeq ($(BONUS),true)
	
	SRCS			=	$(SRCS_MANDATORY)						\
						bonus/fps_bonus.c			\
						bonus/game_loop_bonus.c		\
						bonus/mlx_bonus.c

endif						

OBJS						=		$(SRCS:%.c=$(OBJS_DIR)/%.o)

HEADERS						=		$(HEADER_DIR)/$(NAME).h

CC							=		cc

FLAGS						=		-Wall -Werror -Wextra

DFLAGS						=		-fsanitize=address -g3

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

all:								lib $(OBJS_DIR) $(NAME)
									rm -rf $(OBJS_DIR)/bonus/fps_bonus.o
									rm -rf $(OBJS_DIR)/bonus/mlx_bonus.o
									rm -rf $(OBJS_DIR)/bonus/game_loop_bonus.o

$(OBJS_DIR)/%.o:					$(SRCS_DIR)/%.c $(HEADERS)
										$(CC) $(FLAGS) -I/usr/include -Iminilibx-linux -c $< -o $@

$(NAME):							$(OBJS_DIR) $(OBJS) $(HEADERS) $(DLIB)/libft.a Makefile $(MLX_A) 
										$(CC) $(FLAGS) -lm $(OBJS) $(DLIB)/libft.a $(MLX_A) $(MLX_F) -o $(NAME)

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
										$(MAKE) -s fclean -C $(DLIB)

re:
										$(MAKE) fclean all

debug:
										@$(MAKE) fclean all DEBUG=true

bonus:								
										rm -rf $(OBJS_DIR)/mlx/mlx.o
										rm -rf $(OBJS_DIR)/mlx/game_loop.o
										$(MAKE) lib $(NAME) BONUS=true 

.PHONY: all clean fclean re lib debug