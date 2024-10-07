/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:20:57 by bhumeau           #+#    #+#             */
/*   Updated: 2024/10/07 15:14:48 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

static bool	load_addr_textures_big_map(t_textures *tex)
{
	tex->big_map[0].addr = mlx_get_data_addr(tex->big_map[0].img,
			&tex->big_map[0].bits_per_pixel, &tex->big_map[0].line_length,
			&tex->big_map[0].endian);
	tex->big_map[1].addr = mlx_get_data_addr(tex->big_map[1].img,
			&tex->big_map[1].bits_per_pixel, &tex->big_map[1].line_length,
			&tex->big_map[1].endian);
	tex->big_map[2].addr = mlx_get_data_addr(tex->big_map[2].img,
			&tex->big_map[2].bits_per_pixel, &tex->big_map[2].line_length,
			&tex->big_map[2].endian);
	tex->big_map[3].addr = mlx_get_data_addr(tex->big_map[3].img,
			&tex->big_map[3].bits_per_pixel, &tex->big_map[3].line_length,
			&tex->big_map[3].endian);
	tex->big_map[4].addr = mlx_get_data_addr(tex->big_map[4].img,
			&tex->big_map[4].bits_per_pixel, &tex->big_map[4].line_length,
			&tex->big_map[4].endian);
	tex->big_map[5].addr = mlx_get_data_addr(tex->big_map[5].img,
			&tex->big_map[5].bits_per_pixel, &tex->big_map[5].line_length,
			&tex->big_map[5].endian);
	if (!tex->big_map[0].addr || !tex->big_map[1].addr
		|| !tex->big_map[2].addr || !tex->big_map[3].addr
		|| !tex->big_map[4].addr || !tex->big_map[5].addr)
		return (print_error("Failed to get big map address.\n", false));
	return (true);
}

bool	load_textures_big_map(t_data *data, t_textures *tex)
{
	tex->big_map[0].img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/big_map0.xpm", &tex->big_map_width,
			&data->textures.big_map_height);
	tex->big_map[1].img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/big_map1.xpm", &tex->big_map_width,
			&data->textures.big_map_height);
	tex->big_map[2].img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/big_map2.xpm", &tex->big_map_width,
			&data->textures.big_map_height);
	tex->big_map[3].img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/big_map3.xpm", &tex->big_map_width,
			&data->textures.big_map_height);
	tex->big_map[4].img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/big_map4.xpm", &tex->big_map_width,
			&tex->big_map_height);
	tex->big_map[5].img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/big_map5.xpm", &tex->big_map_width,
			&tex->big_map_height);
	if (!tex->big_map[0].img || !tex->big_map[1].img
		|| !tex->big_map[2].img || !tex->big_map[3].img
		|| !tex->big_map[4].img || !tex->big_map[5].img)
		return (print_error("Failed to load big map images.\n", false));
	if (!load_addr_textures_big_map(tex))
		return (false);
	return (true);
}

static void	draw_square_map(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	scale;

	if (400 / data->map.width < 240 / data->map.height)
		scale = 400 / data->map.width;
	else
		scale = 240 / data->map.height;
	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			my_mlx_pixel_put(&data->mlx.img, (data->res_x
					- (data->map.width - 1) * scale) / 2 + x * scale + j,
				(data->res_y - (data->map.height * 0.68 * scale))
				/ 1.8 + y * scale + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_map(t_data *data)
{
	unsigned long	x;
	unsigned long	y;

	x = 0;
	y = 0;
	while (x < data->map.width)
	{
		y = 0;
		while (y < data->map.height)
		{
			if (data->map.map[y][x] == '1')
				draw_square_map(data, x, y, MAP_COLOR_WALL);
			else if (data->map.map[y][x] == '0'
					|| is_player(data->map.map[y][x]))
				draw_square_map(data, x, y, MAP_COLOR_FLOOR);
			else if (data->map.map[y][x] == '2')
				draw_square_map(data, x, y, MAP_COLOR_DOOR);
			else
				draw_square_map(data, x, y, MAP_COLOR_SCROLL);
			y++;
		}
		x++;
	}
}

void	big_map(t_data *data, t_textures *tex)
{
	unsigned int	color;
	int				x;
	int				y;

	x = -1;
	while (++x < tex->big_map_width)
	{
		y = -1;
		while (++y < tex->big_map_height)
		{
			color = get_pixel(tex->big_map, data->frame_map / 5, x, y);
			if (color != 0xFF000000)
				my_mlx_pixel_put(&data->mlx.img, x + data->res_x / 2
					- tex->big_map_width / 2, y + data->res_y / 1.8
					- tex->big_map_height / 2, color);
		}
	}
	if (data->show_map == 1 && data->frame_map == 0)
		draw_map(data);
	if (data->show_map == 1 && data->frame_map > 0)
		data->frame_map--;
	else if (data->show_map == 2 && data->frame_map < 25)
		data->frame_map++;
	if (data->show_map == 2 && data->frame_map == 25)
		data->show_map = 0;
}
