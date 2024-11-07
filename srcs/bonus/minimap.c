/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:44:56 by bhumeau           #+#    #+#             */
/*   Updated: 2024/11/07 18:07:50 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3D.h>

static void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE_MINIMAP_SQUARE)
	{
		j = 0;
		while (j < SIZE_MINIMAP_SQUARE)
		{
			my_mlx_pixel_put(&data->mlx.img, x * SIZE_MINIMAP_SQUARE + j, y * SIZE_MINIMAP_SQUARE + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player_square(t_data *data, int color)
{
	int	i;
	int	j;

	i = SIZE_MINIMAP_SQUARE_PLAYER_START;
	while (i < SIZE_MINIMAP_SQUARE_PLAYER_END)
	{
		j = SIZE_MINIMAP_SQUARE_PLAYER_START;
		while (j < SIZE_MINIMAP_SQUARE_PLAYER_END)
		{
			my_mlx_pixel_put(&data->mlx.img, MINIMAP_PLAYER_SQUARE_DRAW_POSITION + j, MINIMAP_PLAYER_SQUARE_DRAW_POSITION + i, color);
			j++;
		}
		i++;
	}
}

static void	change_value(int *x, int *y, int value_x, int value_y)
{
	*x = value_x;
	*y = value_y;
}

static void	draw_player(t_data *data, void *img)
{
	int	i;
	int	j;
	int	tmp_j;
	int	limit_i;
	int	limit_j;

	i = MINIMAP_PLAYER_LINE_START_WIDTH;
	limit_i = MINIMAP_PLAYER_LINE_END_WIDTH;
	tmp_j = MINIMAP_PLAYER_LINE_START_WIDTH;
	limit_j = MINIMAP_PLAYER_LINE_END_WIDTH;
	if (data->player.plane_x > 0.46)
		change_value(&tmp_j, &limit_j, MINIMAP_PLAYER_LINE_START_SIZE, SIZE_MINIMAP_SQUARE_MIDDLE);
	else if (data->player.plane_x < -0.46)
		change_value(&tmp_j, &limit_j, SIZE_MINIMAP_SQUARE_MIDDLE, MINIMAP_PLAYER_LINE_END_SIZE);
	else if (data->player.plane_y > 0.46)
		change_value(&i, &limit_i, SIZE_MINIMAP_SQUARE_MIDDLE, MINIMAP_PLAYER_LINE_END_SIZE);
	else
		change_value(&i, &limit_i, MINIMAP_PLAYER_LINE_START_SIZE, SIZE_MINIMAP_SQUARE_MIDDLE);
	while (i++ < limit_i)
	{
		j = tmp_j - 1;
		while (++j < limit_j)
			my_mlx_pixel_put(img, MINIMAP_PLAYER_LINE_DRAW_POSITION + i, MINIMAP_PLAYER_LINE_DRAW_POSITION + j, MAP_COLOR_PLAYER);
	}
	draw_player_square(data, MAP_COLOR_PLAYER);
}

void	draw_minimap(t_data *data, t_map *map, int x, int y)
{
	int		i;
	int		j;

	i = -4;
	while (++i < 4)
	{
		j = -4;
		while (++j < 4)
		{
			if (x + j >= 0 && x + j <= (int)map->width - 2 && y + i >= 0
				&& y + i < (int)map->height && map->map[y + i][x + j] != ' ')
			{
				if (map->map[y + i][x + j] == '1')
					draw_square(data, j + 3, i + 3, MAP_COLOR_WALL);
				else if (map->map[y + i][x + j] == 'c'
					|| map->map[y + i][x + j] == 'o')
					draw_square(data, j + 3, i + 3, MAP_COLOR_DOOR);
				else
					draw_square(data, j + 3, i + 3, MAP_COLOR_FLOOR);
			}
			else
				draw_square(data, j + 3, i + 3, MAP_COLOR_EXTERIOR);
		}
	}
	draw_player(data, &data->mlx.img.img);
}
