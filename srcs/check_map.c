/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:51:06 by vdomasch          #+#    #+#             */
/*   Updated: 2024/11/11 12:09:12 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3D.h>

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

bool	is_door(char c)
{
	return (c == 'c' || c == 'o');
}

static bool	is_neighbors_valid(char **map, int i, int j)
{
	return ((map[i - 1][j] == '0' || map[i - 1][j] == '1' || map[i - 1][j] == 'e'
			|| is_door(map[i - 1][j]) || is_player(map[i - 1][j]))
		&& (map[i + 1][j] == '0' || map[i + 1][j] == '1' || map[i + 1][j] == 'e'
			|| is_door(map[i + 1][j]) || is_player(map[i + 1][j]))
		&& (map[i][j - 1] == '0' || map[i][j - 1] == '1' || map[i][j - 1] == 'e'
			|| is_door(map[i][j - 1]) || is_player(map[i][j - 1]))
		&& (map[i][j + 1] == '0' || map[i][j + 1] == '1' || map[i][j + 1] == 'e'
			|| is_door(map[i][j + 1]) || is_player(map[i][j + 1])));
}

bool	check_map(t_data *data, char **map, int player_count)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map.height)
	{
		j = -1;
		while (++j < data->map.width - 1)
		{
			if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '0' && map[i][j] != 'e'
				&& !is_player(map[i][j]) && !is_door(map[i][j]))
				return (print_error("Invalid character in map.\n", false));
			if ((map[i][j] == '0' || is_door(map[i][j]) || is_player(map[i][j]) || map[i][j] == 'e')
				&& ((i == 0 || i == data->map.height - 1 || j == 0
				|| j == data->map.width - 1) || !is_neighbors_valid(map, i, j)))
				return (print_error("Invalid border.\n", false));
			if (is_player(map[i][j]))
				player_count++;
			if (map[i][j] == 'e')
				data->nb_sprites++;
		}
	}
	if (player_count != 1)
		return (print_error("Invalid number of player.\n", false));
	return (true);
}
