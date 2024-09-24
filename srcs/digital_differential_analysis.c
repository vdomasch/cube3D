/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digital_differential_analysis.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:34:54 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/24 16:22:36 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>


void	print_map(t_data *data, t_raycast *raycast)
{
	size_t		x;
	size_t		y;

	x = 0;
	while (x < data->map.height)
	{
		y = 0;
		while (y < data->map.width)
		{
			if (x == raycast->map_x && y == raycast->map_y)
				printf("X");
			else
				printf("%c", data->map.map[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
	printf("\n\n");
}

static void	calculate_dir_ray(t_data *data, t_raycast *raycast, int x)
{
	double	camera_x;

	camera_x = 2 * x / data->res_x - 1;
	raycast->ray_dir_x = data->player.dir_x + data->player.plane_x * camera_x;
	raycast->ray_dir_y = data->player.dir_y + data->player.plane_y * camera_x;
}

static void	calculate_delta_dist(t_data *data, t_raycast *raycast)
{
	raycast->map_x = (int)data->player.pos_x;
	raycast->map_y = (int)data->player.pos_y;
	if (raycast->ray_dir_y == 0)
		raycast->delta_dist_x = 0;
	else if (raycast->ray_dir_x == 0)
		raycast->delta_dist_x = 1;
	else
		raycast->delta_dist_x = fabs(1 / raycast->ray_dir_x);
	if (raycast->ray_dir_x == 0)
		raycast->delta_dist_y = 0;
	else if (raycast->ray_dir_y == 0)
		raycast->delta_dist_y = 1;
	else
		raycast->delta_dist_y = fabs(1 / raycast->ray_dir_y);
}

static void	calculate_step_and_side_dist(t_data *data, t_raycast *raycast)
{
	if (raycast->ray_dir_x < 0)
	{
		raycast->step_x = -1;
		raycast->side_dist_x = (data->player.pos_x - raycast->map_x) * raycast->delta_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_dist_x = (raycast->map_x + 1.0 - data->player.pos_x) * raycast->delta_dist_x;
	}
	if (raycast->ray_dir_y < 0)
	{
		raycast->step_y = -1;
		raycast->side_dist_y = (data->player.pos_y - raycast->map_y) * raycast->delta_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->side_dist_y = (raycast->map_y + 1.0 - data->player.pos_y) * raycast->delta_dist_y;
	}
}

void	digital_differential_analysis(t_data *data, t_raycast *raycast, int x)
{
	calculate_dir_ray(data, raycast, x);
	calculate_delta_dist(data, raycast);
	calculate_step_and_side_dist(data, raycast);
	while (true)
	{
		if (raycast->side_dist_x < raycast->side_dist_y)
		{
			raycast->side_dist_x += raycast->delta_dist_x;
			raycast->map_x += raycast->step_x;
			raycast->side = 0;
		}
		else
		{
			raycast->side_dist_y += raycast->delta_dist_y;
			raycast->map_y += raycast->step_y;
			raycast->side = 1;
		}
		if (data->map.map[raycast->map_y][raycast->map_x] == '1')
		{
			//print_map(data, raycast);	
			break ;
		}
	}
}


