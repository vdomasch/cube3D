/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:17:33 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/03 11:04:56 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int keypress(int keysym, void *mlx)
{
	if (keysym == XK_Escape)
		mlx_loop_end(mlx);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main(void)
{
	void	*mlx;
	void	*win;
	t_data	img;
	int		x;
	int		y;

	x = 0;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "Put pixel!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	while (x < 1920)
	{
		y = 0;
		while (y < 1080)
		{
			my_mlx_pixel_put(&img, x, y, 0x0000FFFF);
			y++;
		}
		x++;
	}
	mlx_hook(win, 2, 1L << 0, keypress, mlx);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
