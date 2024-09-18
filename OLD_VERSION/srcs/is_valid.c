/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:28:08 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/03 12:13:11 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	verify_map(t_map m, char **map, size_t i, size_t j)
{
	if ((i == 0 || j == 0 || i == m.height - 2 || j == m.width - 2)
		&& map[i][j] == '0')
		return (false);
	if (map[i][j] == '0' || map[i][j] == 'N')
	{
		if (i > 0 && map[i - 1][j] != '0'
			&& map[i - 1][j] != '1' && map[i - 1][j] != 'N')
			return (false);
		if (i < m.height - 2 && map[i + 1][j] != '0'
			&& map[i + 1][j] != '1' && map[i + 1][j] != 'N')
			return (false);
		if (j > 0 && map[i][j - 1] != '0'
			&& map[i][j - 1] != '1' && map[i][j - 1] != 'N')
			return (false);
		if (j < m.width && map[i][j + 1] != '0'
			&& map[i][j + 1] != '1' && map[i][j + 1] != 'N')
			return (false);
	}
	return (true);
}

bool	array_check(t_map m, char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < m.height - 1)
	{
		j = 0;
		while (j < m.width - 1)
		{
			if (!verify_map(m, map, i, j))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	is_valid_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (i < 5)
		return (false);
	if (ft_strncmp(path + ft_strlen(path) - 5, ".xpm", 4))
		return (false);
	return (true);
}

bool	is_valid_color(char *color)
{
	int	i;

	i = 0;
	if (color[0] == 'F' || color[0] == 'C')
	{
		i += 2;
		while (color [i] && color[i] != '\n')
		{
			if (!ft_isdigit(color[i]) && color[i] != ',')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

bool	is_valid_direction(char *line)
{
	if ((line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A'))
		return (true);
	return (false);
}
