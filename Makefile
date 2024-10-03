# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 09:42:35 by vdomasch          #+#    #+#              #
#    Updated: 2024/10/03 13:46:25 by bhumeau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############################################################################
#									CUBE3D								#
#############################################################################

NAME						=		cub3d

SRCS_DIR					=		srcs

OBJS_DIR					=		.objs

HEADER_DIR				 	=		includes

DLIB						=		libft

FILES						=		main.c														\
									parse.c														\
									free.c														\
									set_elements.c												\
									set_map.c													\
									check_map.c													\
									set_entities.c												\
									mlx.c														\
									game_loop.c													\
									raycasting.c												\
									digital_differential_analysis.c								\
									minimap.c													\
									door.c														\
									big_map.c
									

OBJS						=		$(FILES:%.c=$(OBJS_DIR)/%.o)

HEADERS						=		$(HEADER_DIR)/$(NAME).h										 \

CC							=		cc

FLAGS						=		-Wall -Werror -Wextra

DFLAGS						=		-fsanitize=address -g3

#############################################################################
#									MINILIBX								#
#############################################################################

MLX			:=	libmlx.a

MLX_D		:=	minilibx-linux/

MLX_F		:= -L ./minilibx-linux -lmlx -lXext -lX11

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

$(OBJS_DIR)/%.o:					$(SRCS_DIR)/%.c $(HEADERS)
										$(CC) $(FLAGS) -I/usr/include -Iminilibx-linux -c $< -o $@

$(NAME):							$(OBJS_DIR) $(OBJS) $(HEADERS) $(DLIB)/libft.a Makefile $(MLX_A)
										$(CC) $(FLAGS) -lm $(OBJS) $(DLIB)/libft.a $(MLX_A) $(MLX_F) -o $(NAME)

$(OBJS_DIR):
										mkdir -p $(OBJS_DIR)

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

.PHONY: all clean fclean re lib debug