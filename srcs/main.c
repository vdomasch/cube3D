/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:48:24 by vdomasch          #+#    #+#             */
/*   Updated: 2024/08/28 10:30:40 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	print_map(t_data *data)
{
	size_t	i;

	i = 0;
	ft_putstr_fd("\nPrinting map...\n", 1);
	while (i++ < data->map.width)
		ft_putchar_fd('-', 1);
	ft_putchar_fd('\n', 1);
	i = 0;
	while (data->map.map[i])
	{
		ft_putstr_fd(data->map.map[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	i = 0;
	while (i++ < data->map.width)
		ft_putchar_fd('-', 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Map printed\n\n", 1);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	while (i >= 0)
	{
		free(map[i]);
		i--;
	}
	free(map);
}

t_data	*init_data_texture(t_data *data)
{
	data->texture.n_path = NULL;
	data->texture.s_path = NULL;
	data->texture.w_path = NULL;
	data->texture.e_path = NULL;
	data->texture.floor_color = -1;
	data->texture.ceiling_color = -1;
	data->texture.floor.img = NULL;
	data->texture.ceiling.img = NULL;
	data->texture.north.img = NULL;
	data->texture.south.img = NULL;
	data->texture.west.img = NULL;
	data->texture.east.img = NULL;
	return (data);
}

t_data	*intit_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		exit(1);
	}
	data->map.map = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->player.direction = 0;
	data->player.x = 0;
	data->player.y = 0;
	data->mlx = NULL;
	data->win = NULL;
	data->res.x = 0;
	data->res.y = 0;
	return (init_data_texture(data));
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_textures	texture;

	if (argc < 2)
	{
		ft_putstr_fd("Error\n Invlaid number of arguments\n", 2);
		return (1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		return (1);
	}
	data = intit_data();
	parsing(data, &texture, argv[1]);
	print_map(data);
	//mlx(data);
	free_map(data->map.map);
	ft_putstr_fd("End!\n", 1);
	return (0);
}
