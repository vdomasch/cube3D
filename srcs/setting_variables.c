/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:38:09 by vdomasch          #+#    #+#             */
/*   Updated: 2024/08/22 15:32:51 by vdomasch         ###   ########.fr       */
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
	if (path[i - 1] != 'm' || path[i - 2] != 'p' || path[i - 3] != 'x' || path[i - 4] != '.')
		return (false);
	return (true);
}

bool	is_valid_color(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]) && color[i] != ',')
			return (false);
		i++;
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

static void	set_path(char c, t_textures *texture, char *path)
{
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
	//void	*mlx;
	//void	*mlx_win;
	//t_image	img;
	//mlx = mlx_init();
	//mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	//img.img = mlx_new_image(mlx, 1920, 1080);
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	//							&img.endian);
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
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	if (c == 'F')
		//texture->floor = img;
		texture->floor_color = color;
	else if (c == 'C')
		//texture->ceiling = img;
		texture->ceiling_color = color;
}

static int	setting_textures_colors(t_textures *texture, int fd)
{
	int		end_reached;
	char	*line;

	(void)texture;
	end_reached = 2;
	while (end_reached)
	{
		line = get_next_line(fd);
		if (line && line[0] != '\n')
		{
			if (line && is_valid_direction(line + 3) && end_reached--)
				set_path(line[0], texture, line + 3);
			else if ((line[0] == 'F' || line[0] == 'C') && is_valid_color(line + 2) && end_reached--)
				set_color(line[0], texture, line + 2);
			else
			{
				ft_putstr_fd("Error\nInvalid argument\n", 2);
				return (1);
			}
		}
		free(line);
	}
	ft_putstr_fd("		Colors set\n", FD_DEBUG);
	return (0);
}

int	setting_variables(t_textures *texture, int fd)
{
	(void)texture;
	ft_putstr_fd("	Setting variables...\n", FD_DEBUG);
	if (setting_textures_colors(texture, fd))
		return (1);
	ft_putstr_fd("	Variables set\n", FD_DEBUG);
	return (0);
}
