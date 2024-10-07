/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:30:56 by vdomasch          #+#    #+#             */
/*   Updated: 2024/10/07 17:03:24 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

static bool	load_textures_addr(t_image *images)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (images[i].height != 64 || images[i].width != 64)
			return (print_error("Textures must be 64x64.\n", false));
		images[i].addr = mlx_get_data_addr(images[i].img,
				&images[i].bits_per_pixel, &images[i].line_length,
				&images[i].endian);
		if (!images[i].addr)
			return (print_error("Failed to get textures address.\n", false));
		i++;
	}
	return (true);
}

static bool	load_textures(void *mlx, t_textures *textures, t_image *images)
{
	images[0].img = mlx_xpm_file_to_image(mlx, textures->no,
			&images[0].width, &images[0].height);
	images[1].img = mlx_xpm_file_to_image(mlx, textures->so,
			&images[1].width, &images[1].height);
	images[2].img = mlx_xpm_file_to_image(mlx, textures->we,
			&images[2].width, &images[2].height);
	images[3].img = mlx_xpm_file_to_image(mlx, textures->ea,
			&images[3].width, &images[3].height);
	images[4].img = mlx_xpm_file_to_image(mlx, "./assets/wooden-door.xpm",
			&images[4].width, &images[4].height);
	if (!images[0].img || !images[1].img || !images[2].img
		|| !images[3].img || !images[4].img)
		return (print_error("Failed to load images.\n", false));
	if (!load_textures_addr(images))
		return (false);
	return (true);
}

int	mlx_initialize(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return (print_error("Failed to initialize mlx.", 1));
	data->mlx.win = mlx_new_window(data->mlx.mlx, WIDTH,
			HEIGHT, "Cub3D");
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
	if (!load_textures(data->mlx.mlx, &data->textures, data->textures.images))
		return (print_error("Failed to load textures.", 1));
	if (!load_textures_big_map(data, data->textures.big_map))
		return (print_error("Failed to load big map textures.", 1));
	return (0);
}
