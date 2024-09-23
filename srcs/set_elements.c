/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:12:18 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/23 13:55:52 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

int	set_color(t_textures *textures, char *line, char orientation)
{
	int	color;
	int	coef;
	int	tmp;

	coef = 0x1000000;
	tmp = 0;
	while (*line && coef)
	{
		color = ft_atoi(line) / 0x100;
		if (color < 0 || color < 0 || color > 0xFF)
			return (print_error("Invalid color.\n", 1));
		while (*line && (ft_isdigit(*line)))
			line++;
		while (*line == ',' || *line == ' ' || *line == '\n')
			line++;
		tmp += color * coef;
		coef /= 0x100;		
	}
	if (coef != 1)
		return (print_error("Invalid color.\n", 1));
	if (orientation == 'F')
		textures->floor_color = color;
	else if (orientation == 'C')
		textures->ceiling_color = color;
	return (orientation);
}

int	set_texture(t_textures *textures, char *path, char orientation)
{
	int		i;
	char	*copy;

	i = 0;
	while (path[ft_strlen(path) - i - 1] == '\n'
		|| path[ft_strlen(path) - i - 1] == ' ')
		i++;
	if (ft_strncmp(&path[ft_strlen(path) - i - 4], ".xpm", 4))
		return (print_error("Invalid file extension.\n", 1));
	while (*path == ' ')
		path++;
	copy = ft_strdup(path);
	if (!copy)
		return (print_error("Malloc failed.\n", 0));
	copy[ft_strlen(copy) - i] = '\0';
	if (orientation == 'N')
		textures->no = copy;
	else if (orientation == 'S')
		textures->so = copy;
	else if (orientation == 'W')
		textures->we = copy;
	else if (orientation == 'E')
		textures->ea = copy;
	return (orientation);
}

bool	set_elemets(t_data *data, int fd)
{
	char	*line;
	int		count;
	int		check;

	count = 0;
	check = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ' && ++count)
			check += set_texture(&data->textures, line + 3, 'N');
		else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ' && ++count)
			check += set_texture(&data->textures, line + 3, 'S');
		else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ' && ++count)
			check += set_texture(&data->textures, line + 3, 'W');
		else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ' && ++count)
			check += set_texture(&data->textures, line + 3, 'E');
		else if (line[0] == 'F' && line[1] == ' ' && ++count)
			check += set_color(&data->textures, line + 2, 'F');
		else if (line[0] == 'C' && line[1] == ' ' && ++count)
			check += set_color(&data->textures, line + 2, 'C');
		free(line);
	}
	if (check != 454 || count != 6)
		return (print_error("Invalid elements.\n", false));
	return (true);
}
