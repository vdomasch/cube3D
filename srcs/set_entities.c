/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:28:25 by bhumeau           #+#    #+#             */
/*   Updated: 2024/09/23 16:46:37 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

void	set_player(t_data *data, size_t i, size_t j)
{
	if (data->map.map[i][j] == 'N')
	{
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
	}
	else if (data->map.map[i][j] == 'S')
	{
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
	}
	else if (data->map.map[i][j] == 'W')
	{
		data->player.dir_x = -1;
		data->player.plane_y = -0.66;
	}
	else if (data->map.map[i][j] == 'E')
	{
		data->player.dir_x = 1;
		data->player.plane_y = 0.66;
	}
}

bool	set_entities(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width - 1)
		{
			if (is_player(data->map.map[i][j]))
			{
				data->player.pos_x = j + 0.5;
				data->player.pos_y = i + 0.5;
				set_player(data, i, j);




				data->player.dir_x = data->map.map[i][j] == 'E' || -(data->map.map[i][j] == 'W');
				data->player.dir_y = data->map.map[i][j] == 'S' || -(data->map.map[i][j] == 'N');
				data->player.plane_x = 
				data->player.plane_y = 
				data->map.map[i][j] = '0';
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}