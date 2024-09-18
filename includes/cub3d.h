/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:55:01 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/18 15:45:12 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

#define WIDTH 1920
#define HEIGHT 1080

typedef struct s_image
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
	int		width;
	int		height;
}			t_map;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int 	floor;
	int 	ceiling;
	int		width;
	int		height;
	t_image *north;
	t_image *south;
	t_image *west;
	t_image *east;
	t_image *floor;
	t_image *ceiling;
}			t_textures;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}			t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
}			t_mlx;

typedef struct	s_data
{
	t_map		*map;
	t_textures	*textures;
	t_player	*player;
	t_mlx		*mlx;
	int 		res_x;
	int 		res_y;
}			t_data;

#endif
