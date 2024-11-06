/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:33:26 by vdomasch          #+#    #+#             */
/*   Updated: 2024/11/06 10:15:39 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3D.h>

inline void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	*(unsigned int *)(img->addr + (y * img->line_length + x
				* (img->bits_per_pixel / 8))) = color;
}

static inline int	get_pixel(t_image *image, int tex_x, int tex_y)
{
	return (*(unsigned int *)(image->addr
		+ (tex_y * image->line_length + tex_x * (image->bits_per_pixel / 8))));
}

static int	find_side(t_raycast *raycast)
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

/*void	put_textures(t_data *data, t_raycast *ray, int x, int y)
{
	int		color;
	int		scaling;
	int		tex_x;
	int		tex_y;
	double	wall_x;

	if (ray->side == 0)
		wall_x = (data->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y);
	else
		wall_x = (data->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x);
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)data->textures.images[find_side(ray)].width);
	if ((ray->side == 0 && ray->ray_dir_x < 0)
		|| (ray->side == 1 && ray->ray_dir_y > 0))
		tex_x = data->textures.images[find_side(ray)].width - tex_x - 1;
	scaling = (y * 256) - HEIGHT * 128 + ray->line_height * 128;
	tex_y = ((scaling * data->textures.images[find_side(ray)].height)
			/ ray->line_height) / 256;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= data->textures.images[find_side(ray)].height)
		tex_y = data->textures.images[find_side(ray)].height - 1;
	color = get_pixel(data->textures.images, tex_x, tex_y);
	my_mlx_pixel_put(&data->mlx.img, x, y, color);
}*/

void	draw_loop(t_data *d, t_raycast *ray, int img_width, int x)
{
	t_image			*current_tex;
	unsigned int	*img_data;
	int				y;

	current_tex = &d->textures.images[ray->tex_num];
	img_data = (unsigned int *)d->mlx.img.addr;
	y = 0;
	while (y < ray->draw_start)
		img_data[(y++) * img_width + x] = d->textures.ceiling_color;
	while (y <= ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (current_tex->height - 1);
		ray->tex_pos += ray->step;
		img_data[(y++) * img_width + x] = get_pixel(current_tex,
				ray->tex_x, ray->tex_y);
	}
	while (y < HEIGHT)
		img_data[(y++) * img_width + x] = d->textures.floor_color;
}

void	draw(t_data *d, t_raycast *ray, int x)
{
	t_image			*current_tex;
	int				img_width;

	ray->tex_num = find_side(ray);
	current_tex = &d->textures.images[ray->tex_num];
	if (ray->side == 0)
		ray->wall_x = d->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = d->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * current_tex->width);
	if ((ray->side == 0 && ray->ray_dir_x < 0)
		|| (ray->side == 1 && ray->ray_dir_y > 0))
		ray->tex_x = current_tex->width - ray->tex_x - 1;
	ray->step = (double)current_tex->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
	img_width = d->mlx.img.line_length / (d->mlx.img.bits_per_pixel / 8);
	draw_loop(d, ray, img_width, x);
}
