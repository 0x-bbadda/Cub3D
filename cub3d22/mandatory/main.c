/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-dahr <med-dahr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:44:58 by bbadda            #+#    #+#             */
/*   Updated: 2025/02/19 23:27:42 by med-dahr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * Normalizes the given angle to be within the range [0, 2π).
 *
 * @param angle The angle to be normalized.
 * @return The normalized angle.
 */
float normal_angl(double angle)
{
	angle = fmod(angle, M_PI * 2);
	if (angle < 0)
		angle = M_PI * 2 + angle;
	return angle;
}

/**
 * Moves the player based on the provided key data.
 * 
 * @param data The key data containing the key code.
 * @param param A pointer to the t_mlx struct.
 */
void move_player(mlx_key_data_t data, void *param)
{
	t_mlx *mlx;
	int move;

	move = 10;
	mlx = (t_mlx *)param;

	// Handle key events
	if (data.key == MLX_KEY_ESC)
		mlx_close_window(mlx->mlx);
	if (data.key == MLX_KEY_W)
	{
		// Move forward
		if (!wall(mlx, mlx->player.x + cos(mlx->player.alpha) * move, mlx->player.y))
			mlx->player.x += cos(mlx->player.alpha) * move;
		if (!wall(mlx, mlx->player.x, mlx->player.y - sin(mlx->player.alpha) * move))
			mlx->player.y -= sin(mlx->player.alpha) * move;
	}
	if (data.key == MLX_KEY_S)
	{
		// Move backward
		if (!wall(mlx, mlx->player.x - cos(mlx->player.alpha) * move, mlx->player.y))
			mlx->player.x -= cos(mlx->player.alpha) * move;
		if (!wall(mlx, mlx->player.x, mlx->player.y + sin(mlx->player.alpha) * move))
			mlx->player.y += sin(mlx->player.alpha) * move;
	}
	if (data.key == MLX_KEY_D)
	{
		// Strafe right
		if (!wall(mlx, mlx->player.x + sin(mlx->player.alpha) * move, mlx->player.y))
			mlx->player.x += sin(mlx->player.alpha) * move;
		if (!wall(mlx, mlx->player.x, mlx->player.y - cos(mlx->player.alpha) * move))
			mlx->player.y += cos(mlx->player.alpha) * move;
	}
	if (data.key == MLX_KEY_A)
	{
		// Strafe left
		if (!wall(mlx, mlx->player.x - sin(mlx->player.alpha) * move, mlx->player.y))
			mlx->player.x -= sin(mlx->player.alpha) * move;
		if (!wall(mlx, mlx->player.x, mlx->player.y + cos(mlx->player.alpha) * move))
			mlx->player.y -= cos(mlx->player.alpha) * move;
	}
	if (data.key == MLX_KEY_R_RIGHT)
		mlx->player.alpha += 0.1;
	if (data.key == MLX_KEY_R_LEFT)
		mlx->player.alpha -= 0.1;

	// Normalize the player's angle
	mlx->player.alpha = normal_angl(mlx->player.alpha);

	// Redraw the scene
	draw(mlx);
}

// int	create_trgb(int r, int g, int b, int a)
// {
// 	return (r << 24 | g << 16 | b << 8 | a);
// }

// int		**get_2d_pixels(mlx_image_t *img)
// {
// 	int	**pixels;
// 	int	i;
// 	int	j;
// 	int	count;
// 	int	*pixel;

// 	i = 0;
// 	count = 0;
// 	if (!img)
// 		return (NULL);
// 	pixels = malloc(sizeof(int *) * img->height);
// 	while (i < (int) img->height)
// 	{
// 		j = 0;
// 		pixel = malloc(sizeof(int) * img->width);
// 		while (j < (int) img->width)
// 		{
// 			pixel[j++] = create_trgb(img->pixels[count], 
// 					img->pixels[count + 1], img->pixels[count + 2], 
// 					img->pixels[count + 3]);
// 			count += 4;
// 		}
// 		pixels[i++] = pixel;
// 	}
// 	return (pixels);
// }

// mlx_image_t	*get_image(mlx_t *mlxx, char *path)
// {
// 	mlx_texture_t	*texture;
// 	mlx_image_t		*img;

// 	texture = mlx_load_png(path);
// 	if (!texture)
// 	{
// 		// free_resources(mlx);
// 		exit(printf("Invalid texture\n"));
// 	}
// 	img = mlx_texture_to_image(mlxx, texture);
// 	if (!img)
// 	{
// 		// free_resources(mlx);
// 		mlx_delete_texture(texture);
// 		exit(printf("getting the image form texture fails\n"));
// 	}
// 	mlx_delete_texture(texture);
// 	return (img);
// }

// void 		init_Image(t_mlx *mlx)
// {
// 	mlx->img.px_north = NULL;
// 	mlx->img.px_south = NULL;
// 	mlx->img.px_east = NULL;
// 	mlx->img.px_west = NULL;

// 	mlx->img.north = NULL;
// 	mlx->img.south = NULL;
// 	mlx->img.east = NULL;
// 	mlx->img.west = NULL;

// 	mlx->img.px_west = NULL;
// 	mlx->img.north = get_image (mlx->mlx, mlx->map.textures[0]);
// 	mlx->img.east = get_image(mlx->mlx, mlx->map.textures[1]);
// 	mlx->img.west = get_image(mlx->mlx, mlx->map.textures[2]);
// 	mlx->img.south = get_image(mlx->mlx, mlx->map.textures[3]);
// 	mlx->img.px_north = get_2d_pixels(mlx->img.north);
// 	mlx->img.px_east = get_2d_pixels(mlx->img.east);
// 	mlx->img.px_south = get_2d_pixels(mlx->img.south);
// 	mlx->img.px_west = get_2d_pixels(mlx->img.west);
// }

int main(int ac, char **av)
{
	t_map		*map;
	t_mlx		mlx;
	t_player	*player;
	mlx.txx = mlx_load_png("/Users/med-dahr/cub3ddd/cub3d22/mandatory/texture/west.png");
	mlx.mlx = NULL;
	mlx.img.img = NULL;
	map = NULL;
	player = NULL;
    if (ac == 2)
	{
		map = malloc(sizeof(t_map));
		check_file_type(av[1]);
		check_valid_map(av[1], &mlx);
		read_and_fill_map(av[1], &mlx);
		// print(&mlx);
		__create_window(&mlx);
		// init_Image(&mlx);
		draw(&mlx);
		mlx_key_hook(mlx.mlx, move_player, &mlx);
    	mlx_loop(mlx.mlx);
	}
	else
		__error(0, 0);
}
