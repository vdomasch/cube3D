/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:44:56 by bhumeau           #+#    #+#             */
/*   Updated: 2024/10/07 12:30:09 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 50)
	{
		j = 0;
		while (j < 50)
		{
			my_mlx_pixel_put(&data->mlx.img, x * 50 + j, y * 50 + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player_square(t_data *data, int color)
{
	int	i;
	int	j;

	i = 18;
	while (i < 32)
	{
		j = 18;
		while (j < 32)
		{
			my_mlx_pixel_put(&data->mlx.img, 100 + j, 100 + i, color);
			j++;
		}
		i++;
	}
}

void	change_value(int *x, int *y, int value_x, int value_y)
{
	*x = value_x;
	*y = value_y;
}

void	draw_player(t_data *data)
{
	int	i;
	int	j;
	int	tmp_j;
	int	limit_i;
	int	limit_j;

	i = 22;
	limit_i = 28;
	tmp_j = 22;
	limit_j = 28;
	if (data->player.plane_x > 0.46)
		change_value(&tmp_j, &limit_j, 10, 25);
	else if (data->player.plane_x < -0.46)
		change_value(&tmp_j, &limit_j, 25, 40);
	else if (data->player.plane_y > 0.46)
		change_value(&i, &limit_i, 25, 40);
	else
		change_value(&i, &limit_i, 10, 25);
	while (i++ < limit_i)
	{
		j = tmp_j - 1;
		while (++j < limit_j)
			my_mlx_pixel_put(&data->mlx.img, 100 + i - 1, 100 + j, MAP_COLOR_P);
	}
	draw_player_square(data, MAP_COLOR_P);
}

void	draw_minimap(t_data *data, int x, int y)
{
	int		i;
	int		j;

	i = -3;
	while (++i < 3)
	{
		j = -3;
		while (++j < 3)
		{
			if (x + j >= 0 && x + j <= (int)data->map.width - 2
				&& y + i >= 0 && y + i < (int)data->map.height)
			{
				if (data->map.map[y + i][x + j] == '1')
					draw_square(data, j + 2, i + 2, MAP_COLOR_W);
				else if (data->map.map[y + i][x + j] == 'c'
					|| data->map.map[y + i][x + j] == 'o')
					draw_square(data, j + 2, i + 2, MAP_COLOR_D);
				else
					draw_square(data, j + 2, i + 2, MAP_COLOR_F);
			}
			else
				draw_square(data, j + 2, i + 2, MAP_COLOR_EXT);
		}
	}
	draw_player(data);
}
