#include "fdf.h"

void	free_all(t_fdf *fdf)
{
	int		i;
	t_mlx	*mlx;

	i = 0;
	mlx = fdf->mlx;
	while (i < fdf->y_max)
	{
		if (fdf->original_map[i])
			free(fdf->original_map[i]);
		i++;
	}
	if (fdf->original_map)
		free(fdf->original_map);
	fdf->mlx = NULL;
}

void	key_move(int key, t_fdf *fdf)
{
	if (key == RIGHT)
		fdf->x_origin += 4;
	else if (key == LEFT)
		fdf->x_origin -= 4;
	else if (key == UP)
		fdf->y_origin -= 4;
	else if (key == DOWN)
		fdf->y_origin += 4;
	else if (key == BIGGER  && fdf->zoom < fdf->mlx->img_mlx->width)
		fdf->zoom+=5;
	else if (key == SMALLER && fdf->zoom > 5)
		fdf->zoom-=5;
	else
		printf("erreur key");;
}

int		key_events(int key, void *param)
{
	t_fdf	*fdf;
	t_mlx	*mlx;

	fdf = (t_fdf *)param;
	mlx = fdf->mlx;
	if (key == QUIT || key == ESC)
	{
		mlx_destroy_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
		free_all(fdf);
		exit (0);
	}
	if (key == CHANGE_PROJECTION)
		change_projection(fdf);
	key_move(key, fdf);
	draw(fdf);
	return (1);
}

void	initialise(t_fdf *fdf, t_mlx *mlx, t_img *img)
{
	img->width = WIDTH;
	img->height = HEIGHT;
	fdf->zoom = 30;
	mlx->mlx_ptr = mlx_init();
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, img->width, img->height);
	img->addr_img = (unsigned int* )mlx_get_data_addr(img->img_ptr,
			&(img->bits_per_pixels), &(img->line_length), &(img->endian));
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, img->width, img->height, 
			"titre window");
	mlx->img_mlx = img;
	fdf->mlx = mlx;
	fdf->projection = PARALLELE;
}

int		main(int argc, const char *argv[])
{
	t_mlx	mlx;
	t_img	img;
	t_fdf	fdf;

	if (argc != 2)
	{
		printf("erreur argv Map");
		return (1);
	}
	initialise(&fdf, &mlx, &img);
	if (!parsing_map(&fdf, argv[1]))
	{
		printf("error arsing map");
		return (0);
	}
	fdf.x_origin = - ((img.width / fdf.zoom) - fdf.x_max) / 2;
	fdf.y_origin = - ((img.height / fdf.zoom) - fdf.y_max ) / 2;
	draw(&fdf);
	mlx_key_hook(mlx.win_ptr, key_events, &fdf);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
