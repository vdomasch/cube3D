/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdomasch <vdomasch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:29:28 by vdomasch          #+#    #+#             */
/*   Updated: 2024/09/25 17:18:44 by vdomasch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cub3d.h>

void	perp_wall_dist(t_raycast *raycast, t_data *data)
{
	if (raycast->side == 0)
		raycast->perp_wall_dist = (raycast->map_x - data->player.pos_x + (1 - raycast->step_x) / 2) / raycast->ray_dir_x;
	else
		raycast->perp_wall_dist = (raycast->map_y - data->player.pos_y + (1 - raycast->step_y) / 2) / raycast->ray_dir_y;
	raycast->perp_wall_dist = fabs(raycast->perp_wall_dist);
}

void	wall_height(t_data *data, t_raycast *raycast)
{
	raycast->line_height = (int)(data->res_y / raycast->perp_wall_dist);
	raycast->draw_start = -raycast->line_height / 2 + data->res_y / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + data->res_y / 2;
	if (raycast->draw_end >= data->res_y)
		raycast->draw_end = data->res_y - 1;
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	get_pixel(t_textures *texture, int tex_num, int x, int y)
{
	char	*dst;

	dst = texture->images[tex_num].addr + (y * texture->images[tex_num].line_length + x * (texture->images[tex_num].bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	put_textures(t_data *data, t_raycast *raycast, int x, int y)
{
	//int		color;
	char	texture_side;
	int		scaling;
	//int		texture_x;
	int		texture_y;
	
	(void)raycast;
	if (raycast->side == 0)
	{
		if (raycast->ray_dir_x > 0)
		{
			texture_side = 'W';
			//my_mlx_pixel_put(&data->mlx.img, x, y, 0x00880000); //ROUGE
		}
		else
		{
			texture_side = 'E';
			//my_mlx_pixel_put(&data->mlx.img, x, y, 0x00008800); //VERT
		}
	}
	else
	{
		if (raycast->ray_dir_y > 0)
		{
			texture_side = 'N';
			//my_mlx_pixel_put(&data->mlx.img, x, y, 0x00000088); //BLEU
		}
		else
		{
			texture_side = 'S';
			//my_mlx_pixel_put(&data->mlx.img, x, y, 0x00DDDD00); //JAUNE
		}
	}
	scaling = (y * 256) - HEIGHT * 128 + raycast->line_height * 128;
	texture_y = ((scaling * data->textures.height) / raycast->line_height) / 256;
	//texture_x = (int)(raycast->line_height * (double)data->textures.width);

	
	//color = get_pixel(&data->textures, texture_side, 10, texture_y);
	my_mlx_pixel_put(&data->mlx.img, x, y, 0x0);
}

/*static void    draw_line(t_info *w, int x)
{
    int    y;
    int    scaling;
    int    color;
    int    texture_y;

    y = w->draw_start;
    //We are going through every pixel of the vertical line and putting it in our buffer img;
    
    //y the same the entire time
    while (y <= w->draw_end)
    {
        // scaling = 1;
        texture_y = ((scaling * w->n_wall.height) / w->line_height) / 256;
        if (texture_y < 0)
            texture_y = 0; //Pour les segfaults dans les coins
        if (texture_y >= w->n_wall.height) //IMAGE TROP GROSSE LOL OU TROP PETITE QUI SAIT
            texture_y = w->n_wall.height - 1;
        color = pixel_color(w, texture_y);
        // color = apply_fog(color);
        pixel_fill(&w->img_buffer, x, y, color);
        y++;
    }
}*/

void	draw(t_data *data, t_raycast *raycast, int x)
{
	int	y;

	y = 0;
	while (y < data->res_y)
	{
		if (y < raycast->draw_start)
			my_mlx_pixel_put(&data->mlx.img, x, y, 0x0000DDDD);
		else if (y >= raycast->draw_start && y <= raycast->draw_end)
			put_textures(data, raycast, x, y);
		else
			my_mlx_pixel_put(&data->mlx.img, x, y, 0x888888);
		
		y++;
	}
}

int	raycasting(t_data *data)
{
	int		x;
	static t_raycast	raycast;

	x = 0;
	while (x <= data->res_x)
	{
		digital_differential_analysis(data, &raycast, x);
		perp_wall_dist(&raycast, data);
		wall_height(data, &raycast);
		draw(data, &raycast, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img.img, 0, 0);
	//mlx_loop_end(data->mlx.mlx);
	return (0);
}