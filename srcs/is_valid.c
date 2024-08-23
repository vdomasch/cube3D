/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:28:08 by vdomasch          #+#    #+#             */
/*   Updated: 2024/08/23 09:29:24 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

bool	is_valid_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (i < 4)
		return (false);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4))
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
	}
	return (true);
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
