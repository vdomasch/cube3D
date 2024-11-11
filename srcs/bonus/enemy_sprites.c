/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:28:02 by vdomasch          #+#    #+#             */
/*   Updated: 2024/11/11 12:21:14 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3D.h>

bool	init_sprites(t_data *data, t_textures *tex)
{
	data->sprites = malloc(sizeof(t_sprites) * data->nb_sprites);
	if (!data->sprites)
		return (print_error("Failed to allocate memory.\n", false));
	printf("here\n");
	tex->sprite_img.img = mlx_xpm_file_to_image(data->mlx.mlx,
			"assets/goblin.xpm", &tex->sprite_img.width,
			&tex->sprite_img.height);
	if (!tex->sprite_img.img)
		return (print_error("Failed to load sprite texture.\n", false));
	tex->sprite_img.addr = mlx_get_data_addr(tex->sprite_img.img,
			&tex->sprite_img.bits_per_pixel,
			&tex->sprite_img.line_length,
			&tex->sprite_img.endian);
	if (!tex->sprite_img.addr)
		return (print_error("Failed to get sprite texture address.\n", false));
	return (true);
}

bool	set_enemy_sprites(t_data *data)
{
	int	i;
	int	j;
	int	index;

	if (data->nb_sprites == 0)
		return (true);
	if (init_sprites(data, &data->textures))
		return (false);
	printf("ici\n");
	i = -1;
	index = 0;
	while (++i < data->map.height - 1)
	{
		j = -1;
		while (++j < data->map.width - 1)
		{
			if (data->map.map[i][j] == 'e')
			{
				data->sprites[index].pos_x = j + 0.5;
				data->sprites[index].pos_y = i + 0.5;
				index++;
			}
		}
	}
	return (true);
}
