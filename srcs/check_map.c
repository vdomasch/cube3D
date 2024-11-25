/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:51:06 by vdomasch          #+#    #+#             */
/*   Updated: 2024/11/25 13:56:46 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3D.h>

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static bool	is_neighbors_valid(char **map, int i, int j)
{
	return ((map[i - 1][j] == '0' || map[i - 1][j] == '1'
			|| is_player(map[i - 1][j]))
		&& (map[i + 1][j] == '0' || map[i + 1][j] == '1'
			|| is_player(map[i + 1][j]))
		&& (map[i][j - 1] == '0' || map[i][j - 1] == '1'
			|| is_player(map[i][j - 1]))
		&& (map[i][j + 1] == '0' || map[i][j + 1] == '1'
			|| is_player(map[i][j + 1])));
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
			if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '0'
				&& !is_player(map[i][j]))
				return (print_error("Invalid character in map.\n", false));
			if ((map[i][j] == '0' || is_player(map[i][j]))
				&& ((i == 0 || i == data->map.height - 1 || j == 0
				|| j == data->map.width - 1) || !is_neighbors_valid(map, i, j)))
				return (print_error("Invalid map.\n", false));
			if (is_player(map[i][j]))
				player_count++;
		}
	}
	if (player_count != 1)
		return (print_error("Invalid number of player.\n", false));
	return (true);
}
