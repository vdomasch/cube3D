/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:29:28 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/24 17:13:40 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

void	perp_wall_dist(t_raycast *raycast)
{
	if(raycast->side == 0) 
		raycast->perp_wall_dist = (raycast->side_dist_x - raycast->delta_dist_x);
	else          
		raycast->perp_wall_dist = (raycast->side_dist_y - raycast->delta_dist_y);
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

void	draw(t_data *data, t_raycast *raycast, int x)
{
	int	y;

	y = 0;
	while (y < data->res_y)
	{
		if (y < raycast->draw_start)
			my_mlx_pixel_put(&data->mlx.img, x, y, 0x0000FFFF);
		else if (y >= raycast->draw_start && y <= raycast->draw_end)
			my_mlx_pixel_put(&data->mlx.img, x, y, 0x00FFFFFF);
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
		perp_wall_dist(&raycast);
		wall_height(data, &raycast);
		draw(data, &raycast, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img.img, 0, 0);
	return (0);
}