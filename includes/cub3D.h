/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:55:01 by vdomasch          #+#    #+#             */
/*   Updated: 2024/11/11 12:18:08 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <../libft/libft.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <math.h>

//used for fps
# include <stdio.h>
# include <time.h>

# define _USE_MATH_DEFINES
# define BASE16 "0123456789ABCDEF"
# define WIDTH 854
# define HEIGHT 480

# define MAP_COLOR_P 0x0
# define MAP_COLOR_WALL 0x606060
# define MAP_COLOR_FLOOR 0x00A5A2A2
# define MAP_COLOR_EXTERIOR 0x0
# define MAP_COLOR_DOOR 0x007D4E26
# define MAP_COLOR_SCROLL 0x00EFBD8A
# define LIMIT 420

typedef struct s_fps
{
	double	last_time;
	double	delta_time; // Time between frames
	double	fps; // Current FPS
	double	frame_times[60]; // Circular buffer for frame times
	int		frame_index; // Current position in circular buffer
	char	fps_str[16]; // String to store FPS text
}	t_fps;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_minimap
{
	unsigned int	size;
	unsigned int	sqr_size;
	unsigned int	sqr_mid;
	unsigned int	sqr_player_start;
	unsigned int	sqr_player_end;
	unsigned int	sqr_player_draw_position;
	unsigned int	pos;
	unsigned int	l_start_width;
	unsigned int	l_end_width;
	unsigned int	l_start_len;
	unsigned int	l_end_len;
}	t_minimap;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_color;
	int		ceiling_color;
	t_image	*images;
	t_image	sprite_img;
	t_image	*big_map;
}	t_textures;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	int		walk_dir;
	int		strafe_dir;
	int		turn_dir;
}	t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_image	img;
	t_image	map;
}	t_mlx;

typedef struct s_sprites
{
	double	dist;
	double	pos_x;
	double	pos_y;
	bool	destroyed;
}	t_sprites;

typedef struct s_data
{
	t_map		map;
	t_textures	textures;
	t_player	player;
	t_mlx		mlx;
	t_minimap	mmap;
	t_sprites	*sprites;
	double		depth_buffer[WIDTH];
	int			nb_sprites;
	bool		move_mouse;
	int			show_map;
	int			frame;
	t_fps		fps;
}	t_data;

typedef struct s_raycast
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	abs_rdir_x;
	double	abs_rdir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	wall_x;
	double	step;
	double	tex_pos;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		tex_num;
	int		tex_x;
	int		tex_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	bool	there_is_door;
}	t_raycast;

int		optimized_raycasting(t_data *data);
void	draw_fps(t_data *data, t_fps *fps);
void	optimized_dda(t_data *data, t_raycast *ray, int x);
void	init_fps(t_fps *fps);
void	update_fps(t_fps *fps);
void	init_minimap(t_data *data);
bool	set_enemy_sprites(t_data *data);

/****************************************************************************/
/*									INIT									*/
/****************************************************************************/

bool	set_elemets(t_data *data, int fd);
bool	set_entities(t_data *data);
bool	set_map(t_data *data, int fd);

/****************************************************************************/
/*									MLX										*/
/****************************************************************************/

int		mlx_initialize(t_data *data);
int		game_loop(t_data *data);
void	mlx(t_data *data);
void	free_mlx(t_data *data);
void	open_close_door(t_data *data);

/****************************************************************************/
/*									DRAW									*/
/****************************************************************************/

void	draw(t_data *d, t_raycast *raycast, int x);
void	draw_minimap(t_data *data, t_map *map, int x, int y);
void	big_map(t_data *data, t_textures *tex);
void	pixel_put(t_image *img, int x, int y, int color);

/****************************************************************************/
/*									UTILS									*/
/****************************************************************************/

bool	check_map(t_data *data, char **map, int player_count);
bool	is_player(char c);
bool	is_door(char c);
int		print_error(char *error, int ret);
void	free_all(t_data *data);

void	draw_sprites(t_data *data);

#endif
