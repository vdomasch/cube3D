/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:29:28 by vdomasch          #+#    #+#             */
/*   Updated: 2024/10/07 14:18:51 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

static void	perp_wall_dist(t_raycast *raycast, t_data *data)
{
	if (raycast->side == 0)
		raycast->perp_wall_dist = (raycast->map_x - data->player.pos_x
				+ (1 - raycast->step_x) / 2) / raycast->ray_dir_x;
	else
		raycast->perp_wall_dist = (raycast->map_y - data->player.pos_y
				+ (1 - raycast->step_y) / 2) / raycast->ray_dir_y;
	raycast->perp_wall_dist = fabs(raycast->perp_wall_dist);
}

static void	wall_height(t_data *data, t_raycast *raycast)
{
	raycast->line_height = (int)(data->res_y / raycast->perp_wall_dist);
	raycast->draw_start = -raycast->line_height / 2 + data->res_y / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + data->res_y / 2;
	if (raycast->draw_end >= data->res_y)
		raycast->draw_end = data->res_y - 1;
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
