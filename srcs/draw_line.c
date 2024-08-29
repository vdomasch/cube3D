/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:56:20 by vdomasch          #+#    #+#             */
/*   Updated: 2024/08/29 15:16:52 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	mlx_put_pixel(t_image *img, int x, int y, int color)
{
	(void)img;
	(void)x;
	(void)y;
	(void)color;
}

static void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= data->res.x)
		return ;
	if (y < 0)
		return ;
	else if (y >= data->res.y)
		return ;
	mlx_put_pixel(&data->img, x, y, color);
}

int	get_pixel_color(void *img, int x, int y)
{
	int		color;
	char	*dst;

	dst = img + (y * 4 * 64 + x * 4);
	color = *(unsigned int *)dst;
	return (color);
}

int	get_pixel_texture_color(t_data *data, t_raycast *raycast, int y)
{
	int	side;

	if (raycast->side == 0)
		side = raycast->ray_dir_x >= 0;
	else
		side = raycast->ray_dir_y >= 0;
	if (side == 0)
		return (get_pixel_color(data->texture.east.img, raycast->wall_x, y));
	else if (side == 1)
		return (get_pixel_color(data->texture.west.img, raycast->wall_x, y));
	else if (side == 2)
		return (get_pixel_color(data->texture.south.img, raycast->wall_x, y));
	else
		return (get_pixel_color(data->texture.north.img, raycast->wall_x, y));
}

void	draw_line(t_data *data, t_raycast *raycast, int x)
{
	int	y;

	y = 0;
	while (y < data->res.y)
	{
		if (y < raycast->draw_start)
			ft_pixel_put(data, x, y, data->texture.ceiling_color);
		else if (y >= raycast->draw_start && y <= raycast->draw_end)
			ft_pixel_put(data, x, y, get_pixel_texture_color(data, raycast, y));
		else
			ft_pixel_put(data, x, y, data->texture.floor_color);
		y++;
	}
}
