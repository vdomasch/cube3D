/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:29:28 by vdomasch          #+#    #+#             */
/*   Updated: 2024/10/26 14:04:16 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3D.h>

static void	calculate_wall_params(t_raycast *ray, t_data *data,
									int x, double *fish_eye_table)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player.pos_x
				+ (1 - ray->step_x) * 0.5) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player.pos_y
				+ (1 - ray->step_y) * 0.5) / ray->ray_dir_y;
	ray->perp_wall_dist *= fish_eye_table[x];
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = (-ray->line_height + HEIGHT) >> 1;
	ray->draw_end = (ray->line_height + HEIGHT) >> 1;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

// Main raycasting function
int	optimized_raycasting(t_data *data)
{
	static t_raycast	ray;
	static double		fish_eye_table[WIDTH];
	double				angle;
	int					i;
	int					x;

	i = 0;
	while (i < WIDTH)
	{
		angle = atan((i - WIDTH / 2) / (WIDTH / 2));
		fish_eye_table[i++] = cos(angle);
	}
	x = 0;
	while (x < WIDTH)
	{
		optimized_dda(data, &ray, x);
		calculate_wall_params(&ray, data, x, fish_eye_table);
		draw(data, &ray, x);
		x++;
	}
	return (0);
}
