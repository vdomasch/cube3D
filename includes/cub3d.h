/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:55:01 by vdomasch          #+#    #+#             */
/*   Updated: 2024/10/03 15:01:02 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <../libft/libft.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <math.h>

# define BASE16 "0123456789ABCDEF"

#define WIDTH 1280
#define HEIGHT 720
#define SIZE_MINIMAP 250
#define MAP_COLOR_P 0x00CC00FF
#define MAP_COLOR_W 0x0000CCFF
#define MAP_COLOR_F 0x000055FF
#define	MAP_COLOR_EXT 0x000000FF

typedef struct	s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_image;

typedef struct s_map
{
	char	**map;
	size_t	width;
	size_t	height;
}			t_map;

typedef struct	s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int 	floor_color;
	int 	ceiling_color;
	int		width;
	int		height;
	int		big_map_width;
	int		big_map_height;
	t_image *images;
	t_image *big_map;
	//t_image south;
	//t_image west;
	//t_image east;
}			t_textures;

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
	int			walk_dir;
	int			strafe_dir;
	int			turn_dir;
}			t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_image	img;
}			t_mlx;

typedef struct	s_data
{
	t_map		map;
	t_textures	textures;
	t_player	player;
	t_mlx		mlx;
	int 		res_x;
	int 		res_y;
	bool		move_mouse;
	int		show_map;
	int			frame_map;
}			t_data;

typedef	struct s_raycast
{
	size_t 		map_x;
	size_t 		map_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_dist;
	bool		there_is_door;
}	t_raycast;

int		print_error(char *, int);
bool	check_map(char **, size_t, size_t, int);
bool	is_player(char);
bool	parsing(t_data *, char *);
bool	set_elemets(t_data *, int);
bool	set_entities(t_data *);
bool	set_map(t_data *, int);
void	mlx(t_data *);
void	free_all(t_data *);
int		raycasting(t_data *data);
void	digital_differential_analysis(t_data *data, t_raycast *raycast, int x);
int		game_loop(t_data *data);
void	move_player(t_data * data, t_player *player);
void	rotate_player(t_player *player);
void 	free_mlx(t_data *);
void 	draw_minimap(t_data *, int, int);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	open_close_door(t_data *data);
bool	load_textures_big_map(t_data *data);
void	big_map(t_data *data);
int		get_pixel(t_image *images, int tex_num, int x, int y);
//void	free_textures(t_textures *);
//void	free_map(t_map *);

#endif
