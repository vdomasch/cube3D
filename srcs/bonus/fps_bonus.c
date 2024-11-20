/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:36:07 by vdomasch          #+#    #+#             */
/*   Updated: 2024/11/18 13:25:31 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static double	get_time(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ((double)ts.tv_sec + (double)ts.tv_nsec / 1e9);
}

void	init_fps(t_fps *fps)
{
	fps->last_time = get_time();
	fps->fps = 0.0;
}

void	draw_fps(t_data *data, t_fps *fps)
{
	double	current_time;
	double	delta_time;

	current_time = get_time();
	delta_time = current_time - fps->last_time;
	if (delta_time > 0.0)
	{
		fps->fps = 1.0 / delta_time;
		snprintf(fps->fps_str, sizeof(fps->fps_str), "FPS: %.1f", fps->fps);
	}
	mlx_string_put(data->mlx.mlx, data->mlx.win,
		WIDTH - 80, 20, 0xFF44FF, fps->fps_str);
	fps->last_time = current_time;
}
