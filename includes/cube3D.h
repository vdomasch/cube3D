/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:49:34 by vdomasch          #+#    #+#             */
/*   Updated: 2024/08/22 15:02:22 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>

#define FD_DEBUG 1

typedef struct	s_image 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_textures
{
	char	*n_path;
	char	*s_path;
	char	*w_path;
	char	*e_path;
	int		floor_color;
	int		ceiling_color;
	t_image	floor;
	t_image	ceiling;
}	t_textures;

typedef struct s_map
{
	char	**map;
	size_t	width;
	size_t	height;
}	t_map;

typedef struct s_player
{
	char 	direction;
	int		x;
	int		y;
}	t_player;

typedef struct s_data
{
	t_textures	texture;
	t_map		map;
	t_player	player;
}	t_data;

void	parsing(t_data *data, t_textures *texture, char *path_map);
int		setting_variables(t_textures *texture, int fd);
void	print_map(t_data *data);
void	flood();

#endif

