/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:20:57 by bhumeau           #+#    #+#             */
/*   Updated: 2024/10/03 15:02:51 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

bool	load_textures_big_map(t_data *data)
{
	data->textures.big_map[0].img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/big_map0.xpm", &data->textures.big_map_width, &data->textures.big_map_height);
	printf("data->textures.big_map_width = %d\n", data->textures.big_map_width);
	data->textures.big_map[1].img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/big_map1.xpm", &data->textures.big_map_width, &data->textures.big_map_height);
	data->textures.big_map[2].img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/big_map2.xpm", &data->textures.big_map_width, &data->textures.big_map_height);
	data->textures.big_map[3].img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/big_map3.xpm", &data->textures.big_map_width, &data->textures.big_map_height);
	data->textures.big_map[4].img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/big_map4.xpm", &data->textures.big_map_width, &data->textures.big_map_height);
	data->textures.big_map[5].img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/big_map5.xpm", &data->textures.big_map_width, &data->textures.big_map_height);
	if (!data->textures.big_map[0].img || !data->textures.big_map[1].img
		|| !data->textures.big_map[2].img || !data->textures.big_map[3].img 
		|| !data->textures.big_map[4].img || !data->textures.big_map[5].img)
		return (print_error("Failed to load big map images.\n", false));
	data->textures.big_map[0].addr = mlx_get_data_addr(data->textures.big_map[0].img, &data->textures.big_map[0].bits_per_pixel, &data->textures.big_map[0].line_length, &data->textures.big_map[0].endian);
	data->textures.big_map[1].addr = mlx_get_data_addr(data->textures.big_map[1].img, &data->textures.big_map[1].bits_per_pixel, &data->textures.big_map[1].line_length, &data->textures.big_map[1].endian);
	data->textures.big_map[2].addr = mlx_get_data_addr(data->textures.big_map[2].img, &data->textures.big_map[2].bits_per_pixel, &data->textures.big_map[2].line_length, &data->textures.big_map[2].endian);
	data->textures.big_map[3].addr = mlx_get_data_addr(data->textures.big_map[3].img, &data->textures.big_map[3].bits_per_pixel, &data->textures.big_map[3].line_length, &data->textures.big_map[3].endian);
	data->textures.big_map[4].addr = mlx_get_data_addr(data->textures.big_map[4].img, &data->textures.big_map[4].bits_per_pixel, &data->textures.big_map[4].line_length, &data->textures.big_map[4].endian);
	data->textures.big_map[5].addr = mlx_get_data_addr(data->textures.big_map[5].img, &data->textures.big_map[5].bits_per_pixel, &data->textures.big_map[5].line_length, &data->textures.big_map[5].endian);
	if (!data->textures.big_map[0].addr || !data->textures.big_map[1].addr || !data->textures.big_map[2].addr || !data->textures.big_map[3].addr || !data->textures.big_map[4].addr || !data->textures.big_map[5].addr)
		return(print_error("Failed to get big map address.\n", false));
	return (true);
}

void	big_map(t_data *data)
{
	int x;
	int y;
	unsigned int color;

	x = 0;
	y = 0;
	color = 0;
	//printf("data->textures.big_map_width = %d\n", data->textures.big_map_width);
	while (x < data->textures.big_map_width)
	{
		y = 0;
		while (y < data->textures.big_map_height)
		{
			color = get_pixel(data->textures.big_map, data->frame_map / 5, x, y);
			if (color != 0xFF000000)
				my_mlx_pixel_put(&data->mlx.img, x + data->res_x / 2 - data->textures.big_map_width / 2, y + data->res_y / 1.8 - data->textures.big_map_height / 2, color);
			y++;
		}
		x++;
	}
	my_mlx_pixel_put(&data->mlx.img, 0, 0, color);
	if (data->show_map == 1 && data->frame_map > 0)
		data->frame_map--;
	else if (data->show_map == 2 && data->frame_map < 25)
		data->frame_map++;
	if (data->show_map == 2 && data->frame_map == 25)
		data->show_map = 0;
	put_big_map(t_data *data);
}
