/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:44:56 by bhumeau           #+#    #+#             */
/*   Updated: 2024/11/08 14:50:51 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3D.h>

static void	draw_square(t_data *data, int x, int y, int color)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	size_square;

	size_square = data->mmap.sqr_size;
	i = 0;
	while (i < size_square)
	{
		j = 0;
		while (j < size_square)
		{
			pixel_put(&data->mlx.img, x * size_square + j,
				y * size_square + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player_square(t_data *data, int color)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	start;
	unsigned int	end;
	unsigned int	pos;

	start = data->mmap.sqr_player_start;
	end = data->mmap.sqr_player_end;
	pos = data->mmap.sqr_player_draw_position;
	i = start;
	while (i < end)
	{
		j = start;
		while (j < end)
		{
			pixel_put(&data->mlx.img, pos + j, pos + i, color);
			j++;
		}
		i++;
	}
}

static inline void	change_value(int *x, int *y, int value_x, int value_y)
{
	*x = value_x;
	*y = value_y;
}

static void	draw_player(t_data *d, void *img)
{
	int	i;
	int	j;
	int	tmp_j;
	int	limit_i;
	int	limit_j;

	i = d->mmap.l_start_width;
	limit_i = d->mmap.l_end_width;
	tmp_j = i;
	limit_j = limit_i;
	if (d->player.plane_x > 0.46)
		change_value(&tmp_j, &limit_j, d->mmap.l_start_len, d->mmap.sqr_mid);
	else if (d->player.plane_x < -0.46)
		change_value(&tmp_j, &limit_j, d->mmap.sqr_mid, d->mmap.l_end_len);
	else if (d->player.plane_y > 0.46)
		change_value(&i, &limit_i, d->mmap.sqr_mid, d->mmap.l_end_len);
	else
		change_value(&i, &limit_i, d->mmap.l_start_len, d->mmap.sqr_mid);
	while (i++ < limit_i)
	{
		j = tmp_j - 1;
		while (++j < limit_j)
			pixel_put(img, d->mmap.pos + i, d->mmap.pos + j, MAP_COLOR_P);
	}
	draw_player_square(d, MAP_COLOR_P);
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
