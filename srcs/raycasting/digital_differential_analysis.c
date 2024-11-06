/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digital_differential_analysis.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:34:54 by vdomasch          #+#    #+#             */
/*   Updated: 2024/10/26 14:03:20 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3D.h>

static void	update_frame_constants(t_data *data, double *plane_x_cache,
						double *plane_y_cache)
{
	*plane_x_cache = data->player.plane_x;
	*plane_y_cache = data->player.plane_y;
}

static inline void	calculate_step_x(t_raycast *ray,
			t_data *data, double ray_dir_x)
{
	if (ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.pos_x)
			* ray->delta_dist_x;
	}
}

static inline void	calculate_step_y(t_raycast *ray,
			t_data *data, double ray_dir_y)
{
	if (ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.pos_y)
			* ray->delta_dist_y;
	}
}

static void	calculation(t_data *data, t_raycast *ray, int x)
{
	static double	inv_width = 2.0 / WIDTH;
	static double	plane_x_cache;
	static double	plane_y_cache;
	double			camera_x;

	if (x == 0)
		update_frame_constants(data, &plane_x_cache, &plane_y_cache);
	camera_x = x * inv_width - 1.0;
	ray->ray_dir_x = data->player.dir_x + plane_x_cache * camera_x;
	ray->ray_dir_y = data->player.dir_y + plane_y_cache * camera_x;
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	ray->abs_rdir_x = fabs(ray->ray_dir_x);
	ray->abs_rdir_y = fabs(ray->ray_dir_y);
	if (ray->abs_rdir_x < 1e-8)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = 1.0 / ray->abs_rdir_x;
	if (ray->abs_rdir_y < 1e-8)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = 1.0 / ray->abs_rdir_y;
	calculate_step_x(ray, data, ray->ray_dir_x);
	calculate_step_y(ray, data, ray->ray_dir_y);
}

void	optimized_dda(t_data *data, t_raycast *ray, int x)
{
	char	current_cell;

	calculation(data, ray, x);
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		current_cell = data->map.map[ray->map_y][ray->map_x];
		if (current_cell == '1' || current_cell == 'c')
		{
			ray->there_is_door = (current_cell == 'c');
			break ;
		}
	}
}
