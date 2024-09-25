/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:48:21 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/25 14:20:35 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

void	free_mlx(t_data *data)
{
	mlx_destroy_image(data->mlx.mlx, data->mlx.img.img);
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
}

bool	load_textures(t_data *data)
{
	data->textures.north.img = mlx_xpm_file_to_image(data->mlx.mlx, data->textures.no, &data->textures.width, &data->textures.height);
	data->textures.south.img = mlx_xpm_file_to_image(data->mlx.mlx, data->textures.so, &data->textures.width, &data->textures.height);
	data->textures.west.img = mlx_xpm_file_to_image(data->mlx.mlx, data->textures.we, &data->textures.width, &data->textures.height);
	data->textures.east.img = mlx_xpm_file_to_image(data->mlx.mlx, data->textures.ea, &data->textures.width, &data->textures.height);
	if (!data->textures.north.img || !data->textures.south.img || !data->textures.west.img || !data->textures.east.img)
		return (print_error("Failed to load textures.", false));
	data->textures.north.addr = mlx_get_data_addr(data->textures.north.img, &data->textures.north.bits_per_pixel,
			&data->textures.north.line_length, &data->textures.north.endian);
	data->textures.south.addr = mlx_get_data_addr(data->textures.south.img, &data->textures.south.bits_per_pixel,
			&data->textures.south.line_length, &data->textures.south.endian);
	data->textures.west.addr = mlx_get_data_addr(data->textures.west.img, &data->textures.west.bits_per_pixel,
			&data->textures.west.line_length, &data->textures.west.endian);
	data->textures.east.addr = mlx_get_data_addr(data->textures.east.img, &data->textures.east.bits_per_pixel,
			&data->textures.east.line_length, &data->textures.east.endian);
	if (!data->textures.north.addr || !data->textures.south.addr || !data->textures.west.addr || !data->textures.east.addr)
		return (print_error("Failed to get textures address.", false));
	return (true); 
}

int	mlx_initialize(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return (print_error("Failed to initialize mlx.", 1));
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->res_x, data->res_y, "Cub3D");
	if (!data->mlx.win)
		return (print_error("Failed to create window.", 1));
	data->mlx.img.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	if (!data->mlx.img.img)
		return (print_error("Failed to create image.", 1));
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img, &data->mlx.img.bits_per_pixel,
			&data->mlx.img.line_length, &data->mlx.img.endian);
	if (!data->mlx.img.addr)
		return (print_error("Failed to get image address.", 1));
	if (!load_textures(data))
		return (print_error("Failed to load textures.", 1));
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx.mlx);
	if (keycode == XK_w)
		data->player.walk_dir = 1;
	if (keycode == XK_s)
		data->player.walk_dir = -1;
	if (keycode == XK_a)
		data->player.strafe_dir = -1;
	if (keycode == XK_d)
		data->player.strafe_dir = 1;
	if (keycode == XK_Left)
		data->player.turn_dir = 1;
	if (keycode == XK_Right)
		data->player.turn_dir = -1;
	//if (data->player.walk_dir || data->player.strafe_dir)
	//	move_player(data, &data->player);
	//if (data->player.turn_dir)
	//	rotate_player(data, &data->player);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == XK_w)// && data->player.walk_dir == 1)
		data->player.walk_dir = 0;
	if (keycode == XK_s)// && data->player.walk_dir == -1)
		data->player.walk_dir = 0;
	if (keycode == XK_a)// && data->player.strafe_dir == -1)
		data->player.strafe_dir = 0;
	if (keycode == XK_d)// && data->player.strafe_dir == 1)
		data->player.strafe_dir = 0;
	if (keycode == XK_Left)// && data->player.turn_dir == -1)
		data->player.turn_dir = 0;
	if (keycode == XK_Right)// && data->player.turn_dir == 1)
		data->player.turn_dir = 0;
	return (0);
}

void	mlx(t_data *data)
{
	mlx_initialize(data);
	mlx_hook(data->mlx.win, 17, 1L << 3, mlx_loop_end, data->mlx.mlx);
	mlx_hook(data->mlx.win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx.mlx, game_loop, data);
	mlx_loop(data->mlx.mlx);

	
	free_mlx(data);
}
