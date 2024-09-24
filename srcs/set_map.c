/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:14:18 by bhumeau           #+#    #+#             */
/*   Updated: 2024/09/24 11:39:36 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

void	is_line_longer(char *line, t_data *data)
{
	if (ft_strlen(line) > data->map.width)
		data->map.width = ft_strlen(line);
}

char	*skip_empty_line(int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		else
			break ;
	}
	return (line);
}

bool	init_map_line(char **line, char **map_line, int fd)
{
	*line = skip_empty_line(fd);
	*map_line = ft_strdup("");
	if (!*map_line)
	{
		if (*line)
			free(*line);
		return (false);
	}
	return (true);
}

bool	set_map(t_data *data, int fd)
{
	char	*line;
	char	*map_line;

	if (!init_map_line(&line, &map_line, fd))
		return (print_error("Malloc failed.\n", false));
	while (line || get_next_line(fd, &line) > 0)
	{
		is_line_longer(line, data);
		map_line = ft_strfreejoin(map_line, line);
		if (is_empty_line(line))
		{
			free(line);
			free(map_line);
			return (print_error("Empty line in map.\n", false));
		}
		free(line);
		line = NULL;
		if (!map_line)
			return (false);
		data->map.height++;
	}
	data->map.map = split_size_free(map_line, '\n', data->map.width);
	if (!data->map.map)
		return (print_error("Malloc failed.\n", false));
	return (true);
}
