/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:15:43 by bhumeau           #+#    #+#             */
/*   Updated: 2024/09/25 16:52:52 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

int	print_error(char *error, int ret)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(error, 2);
	return (ret);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->map.map = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->textures.no = NULL;
	data->textures.so = NULL;
	data->textures.we = NULL;
	data->textures.ea = NULL;
	data->textures.floor_color = -1;
	data->textures.ceiling_color = -1;
	data->textures.width = 0;
	data->textures.height = 0;
	data->player.pos_x = 0;
	data->player.pos_y = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	data->player.move_speed = 0.05;
	data->player.rot_speed = 0.025;
	data->res_x = WIDTH;
	data->res_y = HEIGHT;
	data->textures.images = malloc(sizeof(t_image) * 4);
	if (!data->textures.images)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = init_data();
	if (!data)
		return (print_error("Failed to allocate memory.", 1));
	if (argc != 2)
		return (print_error("Invalid number of argument.", 1));
	parsing(data, argv[1]);
	mlx(data);
	free_all(data);
	return (0);
}
