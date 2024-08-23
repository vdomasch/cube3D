/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:48:24 by vdomasch          #+#    #+#             */
/*   Updated: 2024/08/22 15:15:15 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	print_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.map[i])
	{
		ft_putstr_fd(data->map.map[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	free_map(t_map map)
{
	int	i;

	i = map.height;
	while (i >= 0)
	{
		free(map.map[i]);
		i--;
	}
	free(map.map);
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
	data->texture.n_path = NULL;
	data->texture.s_path = NULL;
	data->texture.w_path = NULL;
	data->texture.e_path = NULL;
	data->texture.floor_color = -1;
	data->texture.ceiling_color = -1;
	data->texture.floor.img = NULL;
	data->texture.ceiling.img = NULL;
	data->map.map = NULL;
	data->map.width = 0;
	data->map.height = 0;
	return (data);
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
	//print_map(data);
	free_map(data->map);
	ft_putstr_fd("End!\n", 1);
	return (0);
}
