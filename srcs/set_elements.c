/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:12:18 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/19 15:03:43 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

int   read_color(char *line, int *count, int *coef)
{
	int value;
	int color;
	
	color = 0;
	value = ft_atoi(line);
	if (value < 0 || value > 255)
		return (print_error("Invalid color.", -1));
	color += value * (*coef);
	*coef /= 0x100;
	while (ft_isdigit(*line))
		(*line)++;
	(*line)++;
	(*count)++;
	return (color);
}
int	set_color(t_textures *textures, char *line, char orientation)
{
	int		color;
	int		count;
	int		coef;

	coef = 0x10000;
	count = 0;
	while (*line == ' ')
		line++;
	while (count < 3)
	{
		if (ft_isdigit(*line))
			color = read_color(line, &count, &coef);
		else
			return (print_error("Invalid color.", 0));
	}
	if (orientation == 'F')
		textures->floor_color = color;
	else if (orientation == 'C')
		textures->ceiling_color = color;
	return (1);
}

int	mod_b(int *ret_binary, int shift)
{
	*ret_binary <<= shift;
	return (1);
}

int	set_texture(t_textures *textures, char *path, char orientation, int binary)
{
	int 	i;
	char	*copy;
	
	i = 0;
	while (*path + ft_strlen(path) - i == '\n' 
		|| *path + ft_strlen(path) - i == ' ')
		i++;
	if (ft_strncmp(&path[ft_strlen(path) - i - 4], ".xpm", 4))
		return (print_error("Invalid file extension.", 0));
	while (*path == ' ')
		path++;
	copy = ft_strdup(path);
	if (!copy)
		return (print_error("Malloc failed.", 0));
	copy[ft_strlen(path) - i] = '\0';
	if (orientation == 'N' && mod_b(&binary, 6))
		textures->no = copy;
	else if (orientation == 'S' && mod_b(&binary, 5))
		textures->so = copy;
	else if (orientation == 'W' && mod_b(&binary, 4))
		textures->we = copy;
	else if (orientation == 'E' && mod_b(&binary, 3))
		textures->ea = copy;
	return (binary);
}

bool	set_elemets(t_data *data, int fd)
{
	char	*line;
	int		count;
	int		binary;

	count = 0;
	binary = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ' && count++)
			binary += set_texture(data->textures, line + 3, 'N', 1);
		else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ' && count++)
			binary += set_texture(data->textures, line + 3, 'S', 1);
		else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ' && count++)
			binary += set_texture(data->textures, line + 3, 'W', 1);
		else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ' && count++)
			binary += set_texture(data->textures, line + 3, 'E', 1);
		else if (line[0] == 'F' && line[1] == ' ' && count++ && mod_b(&binary, 2))
			binary += set_color(data->textures, line + 2, 'F');
		else if (line[0] == 'C' && line[1] == ' ' && count++ && mod_b(&binary, 1))
			binary += set_color(data->textures, line + 2, 'C');
		free(line);
	}
	if (binary != 127 && count != 6)
		return (print_error("Invalid elements.", false));
	return (true);
}
