/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:10:41 by vdomasch          #+#    #+#             */
/*   Updated: 2024/08/23 08:53:07 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	setting_map(t_data *data, int fd, int i)
{
	char	*line;
	char	*map_line;

	(void)fd;
	(void)i;
	map_line = ft_strdup("");
	if (map_line == NULL)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		exit(1);
	}
	ft_putstr_fd("	Setting map...\n", 1);
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) > data->map.width)
			data->map.width = ft_strlen(line);
		data->map.height++;
		map_line = ft_strfreejoin(map_line, line);
		free(line);
		if (map_line == NULL)
		{
			ft_putstr_fd("Error\nMalloc failed\n", 2);
			exit(1);
		}
	}
	data->map.map = split_size(map_line, '\n', data->map.width);
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		exit(1);
	}
	ft_putstr_fd("	Map set\n", 1);
}

void	set_entities(t_map *m, t_player *p)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < m->height)
	{
		j = 0;
		while (j < m->width)
		{
			if (m->map[i][j] == 'N' || m->map[i][j] == 'S'
				|| m->map[i][j] == 'W' || m->map[i][j] == 'E')
			{
				p->direction = m->map[i][j];
				p->x = j;
				p->y = i;
			}
			j++;
		}
		i++;
	}
}

void	parsing(t_data *data, t_textures *texture, char *path_map)
{
	int	fd;

	(void)texture;
	(void)path_map;
	ft_putstr_fd("Parsing...\n", 1);
	fd = open(path_map, O_RDONLY);
	setting_variables(texture, fd);
	setting_map(data, fd, 13);
	set_entities(&data->map, &data->player);
	ft_putstr_fd("Parsing done\n\n", 1);
}
