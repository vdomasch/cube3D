/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:56:20 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/02 10:01:36 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	mlx_put_pixel(void *img, int x, int y, int color)
{
	printf("			mlx_put_pixel\n");
	(void)img;
	(void)x;
	(void)y;
	(void)color;
	// Color = couleur du pixel
	// img = adresse de l'image
	// x = position en x du pixel a placer
	// y = position en y du pixel a placer
	// mlx_put_pixel permet de placer un pixel de couleur color a la position x, y de l'image img
	printf("			mlx_put_pixel end\n");
}

static void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	printf("		ft_pixel_put\n");
	if (x < 0)
		return ;
	else if (x >= data->res.x - 2)
		return ;
	if (y < 0)
		return ;
	else if (y >= data->res.y - 2)
		return ;
	mlx_put_pixel(&data->img, x, y, color);
	printf("		ft_pixel_put end\n");
}

int	get_pixel_color(t_image *image, char *path, int x, int y)
{
	//need to initmlx befre calling this function

	int color;
	
	(void)image;
	(void)x;
	(void)y;
	image->img = mlx_xpm_file_to_image(mlx, path, &image->width, &image->height);
	
	printf("image->addr = %s, image->bits_per_pixel = %d, image->line_length = %d, image->endian = %d\n", image->addr, image->bits_per_pixel, image->line_length, image->endian);
	image->addr = mlx_get_data_addr(&image.img, &image->bits_per_pixel, &image->line_length, &image->endian);
	printf("image->addr = %s, image->bits_per_pixel = %d, image->line_length = %d, image->endian = %d\n", image->addr, image->bits_per_pixel, image->line_length, image->endian);
	color = image->addr[y * image->line_length + x];
	printf("color = %d\n", color);
	return (color);
}

int	get_pixel_texture_color(t_data *data, t_raycast *raycast, int y)
{
	int	side;
	printf("		get_pixel_texture_color\n");

	if (raycast->side == 0)
		side = raycast->ray_dir_x >= 0;
	else
		side = raycast->ray_dir_y >= 0;
	if (side == 0)
	{
		return (get_pixel_color(&data->texture.east, data->texture.e_path, raycast->wall_x, y));
		printf("		get_pixel_texture_color end 1\n");
	}
	else if (side == 1)
	{
		return (get_pixel_color(&data->texture.west, data->texture.w_path, raycast->wall_x, y));
		printf("		get_pixel_texture_color end 2\n");
	}
	else if (side == 2)
	{
		return (get_pixel_color(&data->texture.south, data->texture.s_path, raycast->wall_x, y));
		printf("		get_pixel_texture_color end 3\n");
	}
	else
	{
		return (get_pixel_color(&data->texture.north, data->texture.n_path, raycast->wall_x, y));
		printf("		get_pixel_texture_color end 4\n");
	}
}

void	draw_line(t_data *data, t_raycast *raycast, int x)
{
	int	y;

	y = 0;
	while (y < data->res.y)
	{
		/*if (y < raycast->draw_start)
			ft_pixel_put(data, x, y, data->texture.ceiling_color);
		else */if (y < raycast->draw_start || (y >= raycast->draw_start && y <= raycast->draw_end))
			ft_pixel_put(data, x, y, get_pixel_texture_color(data, raycast, y));
		else
			ft_pixel_put(data, x, y, data->texture.floor_color);
		y++;
	}
	
}
