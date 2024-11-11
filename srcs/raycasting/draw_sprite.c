/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:46:38 by vdomasch          #+#    #+#             */
/*   Updated: 2024/11/11 12:18:27 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	compute_distances(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_sprites)
	{
		data->sprites[i].dist = pow(data->player.pos_x
				- data->sprites[i].pos_x, 2) + pow(data->player.pos_y
				- data->sprites[i].pos_y, 2);
		i++;
	}
}

void	sort_sprites(t_data *data)
{
	int			i;
	int			j;
	t_sprites	tmp;

	i = 0;
	while (i < data->nb_sprites)
	{
		j = 0;
		while (j < data->nb_sprites - i - 1)
		{
			if (data->sprites[i].dist < data->sprites[i + 1].dist)
			{
				tmp = data->sprites[i];
				data->sprites[i] = data->sprites[i + 1];
				data->sprites[i + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}


static inline int	get_pixel(t_image *image, int tex_x, int tex_y)
{
	return (*(unsigned int *)(image->addr
		+ (tex_y * image->line_length + tex_x * (image->bits_per_pixel / 8))));
}


void	draw_line_sprite(t_data *data, int i, int bbox_x[2], double sprite_size)
{
	int				bbox_y[2];
	int				limit;
	int				j;
	unsigned int	color;

	bbox_y[0] = HEIGHT / 2 - sprite_size / 2;
	bbox_y[1] = HEIGHT / 2 + sprite_size / 2;
	j = 0;
	if (bbox_y[0] > 0)
		j = bbox_y[0];
	limit = bbox_y[1];
	if (limit >= HEIGHT)
		limit = HEIGHT - 1;
	while (j < limit)
	{
		color = get_pixel(data->textures.sprite_img.img,
				((i - bbox_x[0]) * 1.0) / (bbox_x[1] - bbox_x[0]),
				((j - bbox_y[0]) * 1.0) / (bbox_y[1] - bbox_y[0]));
		if (color != 0)
			pixel_put(&data->mlx.img, i, j, color);
		j++;
	}
}

void	draw_sprite(t_data *data, int index,
	double sprite_x, double sprite_size, double transform_y)
{
	int	bbox_x[2];
	int	i;
	int	limit;
	(void)index;

	bbox_x[0] = sprite_x - sprite_size / 2;
	bbox_x[1] = sprite_x + sprite_size / 2;
	//data->sprites[index].killable = !data->sprites[index].is_portal
	//	&& bbox_x[0] < WIDTH / 2 && bbox_x[1] > WIDTH / 2
	//	&& transform_y < 2;
	i = 0;
	if (bbox_x[0] > 0)
		i = bbox_x[0];
	limit = bbox_x[1];
	if (bbox_x[1] >= WIDTH)
		limit = WIDTH - 1;
	while (i <= limit)
	{
		if (transform_y > 0 && transform_y < data->depth_buffer[i])
			draw_line_sprite(data, i, bbox_x, sprite_size);
		i++;
	}
}

void	draw_sprites(t_data *data)
{
	double	sprite_pos_x;
	double	sprite_pos_y;
	double	sprite_size;
	double	sprite_x;
	double	transform_x;
	double	transform_y;
	double	det;
	int		i;

	compute_distances(data);
	sort_sprites(data);
	i = 0;
	while (i < data->nb_sprites)
	{
		sprite_pos_x = data->sprites[i].pos_x + 0.5 - data->player.pos_x;
		sprite_pos_y = data->sprites[i].pos_y + 0.5 - data->player.pos_y;
		det = 1.0 / (data->player.plane_x * data->player.dir_y
				- data->player.dir_x * data->player.plane_y);
		transform_x = det * (data->player.dir_y * sprite_pos_x
				- data->player.dir_x * sprite_pos_y);
		transform_y = det * (-data->player.plane_y * sprite_pos_x
				+ data->player.plane_x * sprite_pos_y);
		sprite_x = (int)((WIDTH / 2)
				* (1 + transform_x / transform_y));
		sprite_size = abs((int)(HEIGHT / transform_y));
		if (!data->sprites[i].destroyed)
			draw_sprite(data, i, sprite_x, sprite_size, transform_y);
		i++;
	}
}
