/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:56:28 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/19 13:44:00 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/cub3d.h>

int	parsing(t_data *data, char *path)
{
	int fd;

	if (ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4))
		return (print_error("Invalid file extension.", 1));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("Can't open file.", 1));
	set_elemets(data, fd);
	return (0);
}
