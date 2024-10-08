/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:38:09 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/20 12:50:17 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	print_error(char *error, int ret)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	return (ret);
}

static void	set_path(char c, t_textures *texture, char *path)
{
	path = ft_substr(path, 0, ft_strlen(path) - 1);
	if (!path)
	{
		print_error("Malloc failed\n", 1);
		return ;
	}
	if (c == 'N')
		texture->n_path = path;
	else if (c == 'S')
		texture->s_path = path;
	else if (c == 'W')
		texture->w_path = path;
	else if (c == 'E')
		texture->e_path = path;
}

static void	set_color(char c, t_textures *texture, char *code_color)
{
	int	color;
	int	coef;

	coef = 0x10000;
	color = 0;
	while (code_color && coef)
	{
		color += ft_atoi(code_color) * coef;
		while (*code_color && *code_color != ',')
			code_color++;
		coef /= 0x100;
		if (*code_color)
			code_color++;
	}
	if (c == 'F')
		texture->floor_color = color;
	else if (c == 'C')
		texture->ceiling_color = color;
}

static int	setting_textures_colors(t_textures *texture, int fd)
{
	int		end_reached;
	char	*line;

	end_reached = 6;
	while (end_reached)
	{
		line = get_next_line(fd);
		if (line && line[0] != '\n')
		{
			if (line && is_valid_direction(line) && is_valid_path(line + 3) && end_reached--)
				set_path(line[0], texture, line + 3);
			else if (is_valid_color(line) && end_reached--)
				set_color(line[0], texture, line + 2);
			else if (line[0] != '\n')
			{
				free(line);
				return (print_error("Invalid argument\n", 1));
			}
			free(line);
		}
	}
	if (end_reached)
		return (print_error("Missing arguments\n", 1));
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else if (line[0] != '\n' && line[0] != '0' && line[0] != '1' && line[0] != ' ')
		{
			printf("line = %s\n", line);
			free(line);
			return (print_error("Invalid argument\n", 1));
		}
		free(line);
	}
	return (0);
}

int	setting_variables(t_textures *texture, int fd)
{
	ft_putstr_fd("	Setting variables...\n", FD_DEBUG);
	if (setting_textures_colors(texture, fd))
		return (1);
	printf("texture->n_path = %s, texture->s_path = %s, texture->w_path = %s, texture->e_path = %s, texture->floor_color = %d, texture->ceiling_color = %d\n", texture->n_path, texture->s_path, texture->w_path, texture->e_path, texture->floor_color, texture->ceiling_color);
	ft_putstr_fd("	Variables set\n", FD_DEBUG);
	return (0);
}
