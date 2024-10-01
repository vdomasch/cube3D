/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhumeau <bhumeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:48:21 by vdomasch          #+#    #+#             */
/*   Updated: 2024/10/01 11:35:46 by bhumeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

bool	load_textures(void *mlx, t_textures *textures)
{
	textures->images[0].img = mlx_xpm_file_to_image(mlx,
			textures->no, &textures->width, &textures->height);
	textures->images[1].img = mlx_xpm_file_to_image(mlx,
			textures->so, &textures->width, &textures->height);
	textures->images[2].img = mlx_xpm_file_to_image(mlx,
			textures->we, &textures->width, &textures->height);
	textures->images[3].img = mlx_xpm_file_to_image(mlx,
			textures->ea, &textures->width, &textures->height);
	if (!textures->images[0].img || !textures->images[1].img
		|| !textures->images[2].img || !textures->images[3].img)
		return (print_error("Failed to load textures.", false));
	textures->images[0].addr = mlx_get_data_addr(textures->images[0].img, &textures->images[0].bits_per_pixel, &textures->images[0].line_length, &textures->images[0].endian);
	textures->images[1].addr = mlx_get_data_addr(textures->images[1].img, &textures->images[1].bits_per_pixel, &textures->images[1].line_length, &textures->images[1].endian);
	textures->images[2].addr = mlx_get_data_addr(textures->images[2].img, &textures->images[2].bits_per_pixel, &textures->images[2].line_length, &textures->images[2].endian);
	textures->images[3].addr = mlx_get_data_addr(textures->images[3].img, &textures->images[3].bits_per_pixel, &textures->images[3].line_length, &textures->images[3].endian);
	if (!textures->images[0].addr || !textures->images[1].addr || !textures->images[2].addr || !textures->images[3].addr)
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
	if (!load_textures(data->mlx.mlx, &data->textures))
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
	if (keycode == XK_Shift_L)
	{
		data->player.move_speed *= 1.5;
		data->player.rot_speed *= 1.5;
	}
	if (keycode == XK_q && data->move_mouse == 0)
	{
		data->move_mouse = 1;
		mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->res_x / 2, data->res_y / 2);
	}
	else if (keycode == XK_q && data->move_mouse == 1)
		data->move_mouse = 0;
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
	if (keycode == XK_Shift_L)
	{
		data->player.move_speed /= 1.5;
		data->player.rot_speed /= 1.5;
	}
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
