/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 10:10:41 by vdomasch          #+#    #+#             */
/*   Updated: 2024/08/21 10:46:11 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	set_path(char* str, t_data *data, char *path)
{
	if (ft_strncmp(str,"NO", 3) == 0)
		data->no_path = path;
	else if (ft_strncmp(str, "SO", 3) == 0)
		data->so_path = path;
	else if (ft_strncmp(str, "WE", 3) == 0)
		data->we_path = path;
	else if (ft_strncmp(str, "EA", 3) == 0)
		data->ea_path = path;
}

int setting_textures(t_data *data, char **argv)
{
	int i = 1;
	
	(void)data;
	(void)argv;
	ft_putstr_fd("		Setting textures...\n", 1);
	while(i < 9)
	{
		if (ft_strncmp(argv[i], "NO", 3) == 0)
			set_path("NO", data, argv[++i]);	
		else if (ft_strncmp(argv[i], "SO", 3) == 0)
			set_path("SO", data, argv[++i]);
		else if (ft_strncmp(argv[i], "WE", 3) == 0)
			set_path("WE", data, argv[++i]);
		else if (ft_strncmp(argv[i], "EA", 3) == 0)
			set_path("EA", data, argv[++i]);
		else
		{
			ft_putstr_fd("Error\nInvalid texture argument\n", 2);
			return (1);
		}
		i++;
	}
	ft_putstr_fd("		Textures set\n", 1);
	return (0);
}

void	set_color(char c, t_data *data, char *color)
{
	(void)data;
	(void)color;
	if (c == 'F')
		;
	else if (c == 'C')
		;
}

int setting_colors(t_data *data, char **argv)
{
	int i = 9;
	
	(void)data;
	(void)argv;
	ft_putstr_fd("		Setting colors...\n", 1);
	while(i < 13)
	{
		if (argv[i][0] == 'F')
			set_color('F', data, argv[++i]);	
		else if (argv[i][0] == 'C')
			set_color('C', data, argv[++i]);
		else
		{
			ft_putstr_fd("Error\nInvalid color argument\n", 2);
			return (1);
		}
		i++;
	}
	ft_putstr_fd("		Colors set\n", 1);
	return (0);
}

int	setting_variables(t_data *data, char **argv)
{
	(void)data;
	(void)argv;
	ft_putstr_fd("	Setting variables...\n", 1);
	if (setting_textures(data, argv))
		return (1);
	if (setting_colors(data, argv))
		return (1);
	ft_putstr_fd("	Variables set\n", 1);
	return (0);
}

void	parsing(t_data *data, char **argv)
{
	(void)data;
	(void)argv;
	ft_putstr_fd("Parsing...\n", 1);
	setting_variables(data, argv);
	//setting_map(argv);
	ft_putstr_fd("Parsing done\n\n", 1);
}