/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:00:12 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/25 15:51:16 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

void	free_map(char **map, int height)
{
	while (height >= 0)
	{
		free(map[height]);
		height--;
	}
	free(map);
}

void	free_all(t_data *data)
{
	if (data->textures.no)
		free(data->textures.no);
	if (data->textures.so)
		free(data->textures.so);
	if (data->textures.we)
		free(data->textures.we);
	if (data->textures.ea)
		free(data->textures.ea);
	if (data->textures.images)
		free(data->textures.images);
	if (data->map.map)
		free_map(data->map.map, data->map.height);
	free(data);
}
