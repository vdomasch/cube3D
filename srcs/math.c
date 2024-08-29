/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:08:37 by vdomasch          #+#    #+#             */
/*   Updated: 2024/08/29 15:09:29 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	calculate_wall_dist(t_data *data, t_raycast *raycast)
{
	if (raycast->side == 0)
		raycast->wall_dist = (raycast->map_x - data->player.pos_x
				+ (1 - raycast->step_x) / 2) / raycast->ray_dir_x;
	else
		raycast->wall_dist = (raycast->map_y - data->player.pos_y
				+ (1 - raycast->step_y) / 2) / raycast->ray_dir_y;
}

void	calculate_line_height(t_data *data, t_raycast *raycast)
{
	raycast->line_height = (int)(data->res.y / raycast->wall_dist);
	raycast->draw_start = -raycast->line_height / 2 + data->res.y / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + data->res.y / 2;
	if (raycast->draw_end >= data->res.y)
		raycast->draw_end = data->res.y - 1;
}

void	init_raycast(t_raycast *raycast)
{
	raycast->ray_dir_x = 0;
	raycast->ray_dir_y = 0;
	raycast->delta_dist_x = 0;
	raycast->delta_dist_y = 0;
	raycast->side_dist_x = 0;
	raycast->side_dist_y = 0;
	raycast->map_x = 0;
	raycast->map_y = 0;
	raycast->step_x = 0;
	raycast->step_y = 0;
	raycast->side = 0;
	raycast->wall_dist = 0;
	raycast->line_height = 0;
	raycast->draw_start = 0;
	raycast->draw_end = 0;
}

void	raycasting(t_data *data)
{
	int			x;
	t_raycast	raycast;

	x = 0;
	init_raycast(&raycast);
	while (x < data->res.x)
	{
		raycast.map_x = (int)data->player.pos_x;
		raycast.map_y = (int)data->player.pos_y;
		digital_differential_analysis(data, &raycast, x);
		calculate_wall_dist(data, &raycast);
		calculate_line_height(data, &raycast);
		draw_line(data, &raycast, x);
		x++;
	}
}
