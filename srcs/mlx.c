/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:48:21 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/24 16:41:59 by vdomasch         ###   ########.fr       */
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
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		mlx_loop_end(data->mlx.mlx);
	if (keycode == XK_W)
		data->player.walk_dir = 1;
	if (keycode == XK_S)
		data->player.walk_dir = -1;
	if (keycode == XK_A)
		data->player.strafe_dir = -1;
	if (keycode == XK_D)
		data->player.strafe_dir = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == XK_W || keycode == XK_S)
		data->player.walk_dir = 0;
	if (keycode == XK_A || keycode == XK_D)
		data->player.strafe_dir = 0;
	return (0);
}

int	render_next_frame(t_data *data)
{
	mlx_clear_window(data->mlx.mlx, data->mlx.win);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img.img, 0, 0);
	return (0);
}

void	mlx(t_data *data)
{
	mlx_initialize(data);
	mlx_hook(data->mlx.win, 17, 1L << 3, mlx_loop_end, data->mlx.mlx);
	mlx_hook(data->mlx.win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx.mlx, raycasting, data);
	mlx_loop(data->mlx.mlx);

	
	free_mlx(data);
}
