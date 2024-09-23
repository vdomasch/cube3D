/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:14:18 by bhumeau           #+#    #+#             */
/*   Updated: 2024/09/23 16:26:27 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

bool	is_neighbors_valid(char **map, size_t i, size_t j)
{
	return ((map[i - 1][j] == '0' || map[i - 1][j] == '1'
			|| is_player(map[i - 1][j]))
		&& (map[i + 1][j] == '0' || map[i + 1][j] == '1'
			|| is_player(map[i + 1][j]))
		&& (map[i][j - 1] != '0' || map[i][j - 1] != '1'
			|| is_player(map[i][j - 1]))
		&& (map[i][j + 1] != '0' || map[i][j + 1] != '1'
			|| is_player(map[i][j + 1])));
}

bool	check_map(char **map, size_t width, size_t height, int player_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width - 1)
		{
			if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '0'
				&& !is_player(map[i][j]))
				return (print_error("Invalid character in map.\n", false));
			if (map[i][j] == '0' && ((i == 0 || i == height - 1 || j == 0
				|| j == width - 1) || !is_neighbors_valid(map, i, j)))
				return (print_error("Invalid border.\n", false));
			if (is_player(map[i][j]))
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (print_error("Invalid number of player.\n", false));
	return (true);
}

char	*skip_empty_line(int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '\0')
		{
			free(line);
			continue ;
		}
		else
			break ;
	}
	return (line);
}

bool	set_map(t_data *data, int fd)
{
	char	*line;
	char	*map_line;

	line = skip_empty_line(fd);
	if (!line)
		return (print_error("Missing map.\n", false));
	map_line = ft_strdup("");
	if (!map_line)
		return (print_error("Malloc failed.\n", false));
	while (line || get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(line) > data->map.width)
			data->map.width = ft_strlen(line);
		map_line = ft_strfreejoin(map_line, line);
		free(line);
		line = NULL;
		if (!map_line)
			return (false);
		data->map.height++;
	}
	data->map.map = split_size(map_line, '\n', data->map.width);
	if (!data->map.map)
		return (print_error("Malloc failed.\n", false));
	return (true);
}
