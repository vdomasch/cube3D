/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:28 by vdomasch          #+#    #+#             */
/*   Updated: 2024/10/07 12:28:13 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/cub3d.h>

/*void	print_elements(t_data *data)
{
	printf("data->textures.no = %s\n", data->textures.no);
	printf("data->textures.so = %s\n", data->textures.so);
	printf("data->textures.we = %s\n", data->textures.we);
	printf("data->textures.ea = %s\n", data->textures.ea);
	printf("data->textures.floor_color = %X\n", data->textures.floor_color);
	printf("data->textures.ceiling_color = %X\n", data->textures.ceiling_color);
}*/

bool	parsing(t_data *data, char *path)
{
	int	fd;

	if (ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4))
		return (print_error("Invalid file extension.", false));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("Can't open file.", false));
	if (!set_elemets(data, fd))
		return (false);
	if (!set_map(data, fd))
		return (false);
	close(fd);
	if (!check_map(data->map.map, data->map.width, data->map.height, 0))
		return (false);
	if (!set_entities(data))
		return (false);
	return (true);
}
