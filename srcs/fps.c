/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:36:07 by vdomasch          #+#    #+#             */
/*   Updated: 2024/10/26 13:50:00 by vdomasch         ###   ########.fr       */
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
	int	i;

	fps->last_time = get_time();
	fps->delta_time = 0.0;
	fps->fps = 0.0;
	fps->frame_index = 0;
	i = 0;
	while (i < 60)
		fps->frame_times[i++] = 0.0;
}

void	update_fps(t_fps *fps)
{
	double	current_time;
	double	total_time;
	int		i;

	current_time = get_time();
	fps->delta_time = current_time - fps->last_time;
	fps->last_time = current_time;
	// Store frame time in circular buffer
	fps->frame_times[fps->frame_index] = fps->delta_time;
	fps->frame_index = (fps->frame_index + 1) % 60;
	// Calculate average FPS over last 60 frames
	total_time = 0.0;
	i = 0;
	while (i < 60)
		total_time += fps->frame_times[i++];
	if (total_time > 0.0)
		fps->fps = 60.0 / total_time;
	// Update FPS string
	snprintf(fps->fps_str, sizeof(fps->fps_str), "FPS: %.1f", fps->fps);
}

// Function to draw text on screen using MLX
static void	draw_text(t_data *data, char *str, int x, int y, int color)
{
	mlx_string_put(data->mlx.mlx, data->mlx.win, x, y, color, str);
}

void	draw_fps(t_data *data, t_fps *fps)
{
	// Draw FPS counter in top-left corner
	// White text with black outline for better visibility
	draw_text(data, fps->fps_str, 11, 21, 0x000000);//Black shadow
	draw_text(data, fps->fps_str, 9, 21, 0x000000);
	draw_text(data, fps->fps_str, 10, 22, 0x000000);
	draw_text(data, fps->fps_str, 10, 20, 0x000000);
	draw_text(data, fps->fps_str, 10, 21, 0xFFFFFF); // White text
}
