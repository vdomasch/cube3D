/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:11:44 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/24 16:11:14 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_press(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_loop_end(data->mlx);
	if (keysym == XK_w || keysym == XK_Up)
	{
		data->player.pos_x += data->player.dir_x * data->player.move_speed;
		data->player.pos_y += data->player.dir_y * data->player.move_speed;
	}
	if (keysym == XK_s || keysym == XK_Down)
	{
		data->player.pos_x -= data->player.dir_x * data->player.move_speed;
		data->player.pos_y -= data->player.dir_y * data->player.move_speed;
	}
	if (keysym == XK_a || keysym == XK_Left)
	{
		data->player.pos_x -= data->player.plane_x * data->player.move_speed;
		data->player.pos_y -= data->player.plane_y * data->player.move_speed;
	}
	if (keysym == XK_d || keysym == XK_Right)
	{
		data->player.pos_x += data->player.plane_x * data->player.move_speed;
		data->player.pos_y += data->player.plane_y * data->player.move_speed;
	}
	return (0);
}

void	clean_mlx(t_data *data)
{
	if (data->mlx)
	{
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	map_gen(t_data *data, void *mlx, void *win)
{
	(void)data;
	(void)mlx;
	(void)win;
	return (0);
}

/*int	image_loader(t_data *data, void *mlx)
{
	printf("image_loader\n");
	printf("data->texture.n_path = %s, data->texture.s_path = %s, data->texture.w_path = %s, data->texture.e_path = %s\n", data->texture.n_path, data->texture.s_path, data->texture.w_path, data->texture.e_path);
	data->texture.north.img = mlx_xpm_file_to_image(mlx, data->texture.n_path, &data->texture.width, &data->texture.height);

	data->texture.south.img = mlx_xpm_file_to_image(mlx, data->texture.s_path, &data->texture.width, &data->texture.height);
	
	data->texture.west.img = mlx_xpm_file_to_image(mlx, data->texture.w_path, &data->texture.width, &data->texture.height);
	
	data->texture.east.img = mlx_xpm_file_to_image(mlx, data->texture.e_path, &data->texture.width, &data->texture.height);
	
	printf("data->texture.north.img = %p, data->texture.south.img = %p, data->texture.west.img = %p, data->texture.east.img = %p\n", data->texture.north.img, data->texture.south.img, data->texture.west.img, data->texture.east.img);
	if (!data->texture.north.img || !data->texture.south.img || !data->texture.west.img || !data->texture.east.img)
		return (1);
	return (0);
}*/


int	mlx_launch(t_data *data)
{
	printf("mlx_launch\n");
	/*if (image_loader(data, data->mlx))
	{
		printf("Error\nImage loader failed\n");
		clean_mlx(data);
		return (1);
	}*/
	data->mlx = mlx_init();
	//if (!data->mlx)
	//	return (2);
	data->win = mlx_new_window(data->mlx, 1920, 1080, "Cub3D");
	//if (!data->win)
	//{
	//	mlx_destroy_display(data->mlx);
	//	free(data->mlx);
	//	return (3);
	//}
	data->img.img = mlx_new_image(data->mlx, 1920, 1080);
	//mlx_do_key_autorepeaton(data->mlx);
	if (!map_gen(data, data->mlx, data->win))
	{
		raycasting(data, &data->img);
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
		mlx_hook(data->win, 17, 1L << 3, mlx_loop_end, data->mlx);
		mlx_hook(data->win, 2, 1L << 0, key_press, data);
		mlx_loop(data->mlx);
	}
	clean_mlx(data);
	printf("mlx_launch end\n");
	return (0);
}
