/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:49:34 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/02 09:58:53 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include <X11/keysym.h>

#define FD_DEBUG 1

typedef struct	s_image 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
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
	t_image	north;
	t_image	south;
	t_image	west;
	t_image	east;
}	t_textures;

typedef struct s_map
{
	char	**map;
	size_t	width;
	size_t	height;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
}	t_player;

typedef struct s_resolution
{
	int	x;
	int	y;
}	t_resolution;

typedef struct s_raycast
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	double	wall_dist;
	double	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_raycast;

typedef struct s_data
{
	t_textures		texture;
	t_map			map;
	t_player		player;
	t_resolution	res;
	void			*mlx;
	void			*win;
	void			*img;	
}	t_data;

int		parsing(t_data *data, t_textures *texture, char *path_map);
int		setting_variables(t_textures *texture, int fd);
void	print_map(t_data *data);
bool	array_check(t_map m, char **map);
bool	is_valid_path(char *path);
bool	is_valid_color(char *color);
bool	is_valid_direction(char *line);
void	mlx(t_data *data);
void	free_map(char **map);
int		print_error(char *error, int ret);
void	raycasting(t_data *data);
void	digital_differential_analysis(t_data *data, t_raycast *raycast, int x);
void	draw_line(t_data *data, t_raycast *raycast, int x);
//int		image_loader(t_data *data, void *mlx);


#endif

