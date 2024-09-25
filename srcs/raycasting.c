/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:29:28 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/25 14:27:33 by vdomasch         ###   ########.fr       */
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
	*(unsigned int*)dst = color;
}

int	get_pixel(t_textures *texture, int tex_num, int x, int y)
{
	char	*dst;

	if (tex_num == 0)
		dst = texture->north.addr + (y * texture->north.line_length + x * (texture->north.bits_per_pixel / 8));
	else if (tex_num == 1)
		dst = texture->south.addr + (y * texture->south.line_length + x * (texture->south.bits_per_pixel / 8));
	else if (tex_num == 2)
		dst = texture->west.addr + (y * texture->west.line_length + x * (texture->west.bits_per_pixel / 8));
	else
		dst = texture->east.addr + (y * texture->east.line_length + x * (texture->east.bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	put_textures(t_data *data, t_raycast *raycast, int x, int y)
{
	int		color;
	int		tex_y;
	int		tex_x;
	double	step;
	double	tex_pos;

	if (raycast->side == 0 || raycast->side == 1)
		tex_pos = (raycast->map_y - data->player.pos_y + (1 - raycast->step_y) / 2) / raycast->ray_dir_y;
	else
		tex_pos = (raycast->map_x - data->player.pos_x + (1 - raycast->step_x) / 2) / raycast->ray_dir_x;
	tex_pos -= floor(tex_pos);
	tex_x = (int)(tex_pos * data->textures.width);
	if ((raycast->side == 0 && raycast->ray_dir_x > 0) || (raycast->side == 1 && raycast->ray_dir_y < 0))
		tex_x = data->textures.width - tex_x - 1;
	step = 1.0 * data->textures.height / raycast->line_height;
	tex_pos = (raycast->draw_start - data->res_y / 2 + raycast->line_height / 2) * step;
	tex_y = (int)tex_pos & (data->textures.height - 1);
	while (raycast->draw_start < raycast->draw_end)
	{
		tex_pos += step;
		tex_y = (int)tex_pos & (data->textures.height - 1);
		color = get_pixel(&data->textures, raycast->side, tex_x, tex_y);
		my_mlx_pixel_put(&data->mlx.img, x, raycast->draw_start, color);
		raycast->draw_start++;
	}
	(void)y;
}

void	draw(t_data *data, t_raycast *raycast, int x)
{
	int	y;

	y = 0;
	while (y < data->res_y)
	{
		if (y < raycast->draw_start)
			my_mlx_pixel_put(&data->mlx.img, x, y, 0x0000FFFF);
		else if (y >= raycast->draw_start && y <= raycast->draw_end)
			//put_textures(data, raycast, x, y);
			my_mlx_pixel_put(&data->mlx.img, x, y, 0x0);
		else
			my_mlx_pixel_put(&data->mlx.img, x, y, 0x00FFFF00);
		y++;
	}
}

int	raycasting(t_data *data)
{
	int		x;
	t_raycast	raycast;

	x = 0;
	while (x <= data->res_x)
	{
		digital_differential_analysis(data, &raycast, x);
		perp_wall_dist(&raycast, data);
		wall_height(data, &raycast);
		draw(data, &raycast, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img.img, 0, 0);
	return (0);
}