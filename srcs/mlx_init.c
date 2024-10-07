/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:30:56 by vdomasch          #+#    #+#             */
/*   Updated: 2024/10/07 13:37:44 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

static bool	load_textures_addr(t_textures *texture)
{
	texture->images[0].addr = mlx_get_data_addr(texture->images[0].img,
			&texture->images[0].bits_per_pixel, &texture->images[0].line_length,
			&texture->images[0].endian);
	texture->images[1].addr = mlx_get_data_addr(texture->images[1].img,
			&texture->images[1].bits_per_pixel, &texture->images[1].line_length,
			&texture->images[1].endian);
	texture->images[2].addr = mlx_get_data_addr(texture->images[2].img,
			&texture->images[2].bits_per_pixel, &texture->images[2].line_length,
			&texture->images[2].endian);
	texture->images[3].addr = mlx_get_data_addr(texture->images[3].img,
			&texture->images[3].bits_per_pixel, &texture->images[3].line_length,
			&texture->images[3].endian);
	texture->images[4].addr = mlx_get_data_addr(texture->images[4].img,
			&texture->images[4].bits_per_pixel, &texture->images[4].line_length,
			&texture->images[4].endian);
	if (!texture->images[0].addr || !texture->images[1].addr
		|| !texture->images[2].addr || !texture->images[3].addr
		|| !texture->images[4].addr)
		return (print_error("Failed to get textures address.\n", false));
	return (true);
}

static bool	load_textures(void *mlx, t_textures *textures)
{
	textures->images[0].img = mlx_xpm_file_to_image(mlx,
			textures->no, &textures->width, &textures->height);
	textures->images[1].img = mlx_xpm_file_to_image(mlx,
			textures->so, &textures->width, &textures->height);
	textures->images[2].img = mlx_xpm_file_to_image(mlx,
			textures->we, &textures->width, &textures->height);
	textures->images[3].img = mlx_xpm_file_to_image(mlx,
			textures->ea, &textures->width, &textures->height);
	textures->images[4].img = mlx_xpm_file_to_image(mlx,
			"./assets/wooden-door.xpm", &textures->width, &textures->height);
	if (!textures->images[0].img || !textures->images[1].img
		|| !textures->images[2].img || !textures->images[3].img \
		|| !textures->images[4].img)
		return (print_error("Failed to load images.\n", false));
	if (!load_textures_addr(textures))
		return (false);
	return (true);
}

int	mlx_initialize(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return (print_error("Failed to initialize mlx.", 1));
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->res_x,
			data->res_y, "Cub3D");
	if (!data->mlx.win)
		return (print_error("Failed to create window.", 1));
	data->mlx.img.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	if (!data->mlx.img.img)
		return (print_error("Failed to create image.", 1));
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img,
			&data->mlx.img.bits_per_pixel, &data->mlx.img.line_length,
			&data->mlx.img.endian);
	if (!data->mlx.img.addr)
		return (print_error("Failed to get image address.", 1));
	if (!load_textures(data->mlx.mlx, &data->textures))
		return (print_error("Failed to load textures.", 1));
	if (!load_textures_big_map(data, &data->textures))
		return (print_error("Failed to load big map textures.", 1));
	return (0);
}
