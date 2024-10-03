/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:29:28 by vdomasch          #+#    #+#             */
/*   Updated: 2024/10/03 16:35:40 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

void	perp_wall_dist(t_raycast *raycast, t_data *data)
{
	if (raycast->side == 0)
		raycast->perp_wall_dist = (raycast->map_x - data->player.pos_x + (1 - raycast->step_x) / 2) / raycast->ray_dir_x;
	else
		raycast->perp_wall_dist = (raycast->map_y - data->player.pos_y + (1 - raycast->step_y) / 2) / raycast->ray_dir_y;
	raycast->perp_wall_dist = fabs(raycast->perp_wall_dist);
}

void	wall_height(t_data *data, t_raycast *raycast)
{
	raycast->line_height = (int)(data->res_y / raycast->perp_wall_dist);
	raycast->draw_start = -raycast->line_height / 2 + data->res_y / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + data->res_y / 2;
	if (raycast->draw_end >= data->res_y)
		raycast->draw_end = data->res_y - 1;
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_image *images, int tex_num, int x, int y)
{
	char	*dst;

	dst = images[tex_num].addr + (y * images[tex_num].line_length + x * (images[tex_num].bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	find_side(t_raycast *raycast)
{
	if (raycast->there_is_door)
		return (4);
	if (raycast->side == 0)
	{
		if (raycast->ray_dir_x > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (raycast->ray_dir_y > 0)
			return (0);
		else
			return (1);
	}
}

void	put_textures(t_data *data, t_raycast *raycast, int x, int y)
{
	int		color;
	char	texture_side;
	int		scaling;
	int		texture_x;
	int		texture_y;
	double	wall_x;

	texture_side = find_side(raycast);
	if (raycast->side == 0)
		wall_x = (data->player.pos_y + raycast->perp_wall_dist * raycast->ray_dir_y);
	else
		wall_x = (data->player.pos_x + raycast->perp_wall_dist * raycast->ray_dir_x);
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * (double)data->textures.width);
	if ((raycast->side == 0 && raycast->ray_dir_x < 0)
		|| (raycast->side == 1 && raycast->ray_dir_y > 0))
		texture_x = data->textures.width - texture_x - 1;
	scaling = (y * 256) - HEIGHT * 128 + raycast->line_height * 128;
	texture_y = ((scaling * data->textures.height) / raycast->line_height) / 256;
	if (texture_y < 0)
		texture_y = 0;
	if (texture_y >= data->textures.height)
		texture_y = data->textures.height - 1;
	color = get_pixel(data->textures.images, texture_side, texture_x, texture_y);
	my_mlx_pixel_put(&data->mlx.img, x, y, color);
}

void	draw(t_data *d, t_raycast *raycast, int x)
{
	int	y;

	y = 0;
	while (y < d->res_y)
	{
		if (!d->show_map && x < SIZE_MINIMAP && y < SIZE_MINIMAP)
			;
		else if (y < raycast->draw_start)
			my_mlx_pixel_put(&d->mlx.img, x, y, d->textures.ceiling_color);
		else if (y >= raycast->draw_start && y <= raycast->draw_end)
			put_textures(d, raycast, x, y);
		else
			my_mlx_pixel_put(&d->mlx.img, x, y, d->textures.floor_color);
		y++;
	}
	raycast->there_is_door = false;
}

int	raycasting(t_data *data)
{
	int					x;
	static t_raycast	raycast;

	x = 0;
	while (x < data->res_x)
	{
		digital_differential_analysis(data, &raycast, x);
		perp_wall_dist(&raycast, data);
		wall_height(data, &raycast);
		draw(data, &raycast, x);
		x++;
	}
	return (0);
}
