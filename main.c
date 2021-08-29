
#include "fdf.h"
#include <string.h>
#include <stdio.h>

#define WIDTH 700
#define HEIGHT 700

void	initialise(t_fdf *fdf, t_mlx *mlx, t_img *img)
{
	img->width = WIDTH;
	img->height = HEIGHT;

	mlx->mlx_ptr = mlx_init();
	img->img_ptr = mlx_new_image(mlx->mlx_ptr, img->width, img->height);
	img->addr_img = mlx_get_data_addr(img->img_ptr, &(img->bits_per_pixels), &(img->line_length), &(img->endian));
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, img->width, img->height, "titre window");
	mlx->img_mlx = img;
	fdf->mlx = mlx;
}

int		main(int argc, const char *argv[])
{
	t_mlx	mlx;
	t_img	img;
	t_fdf	fdf;

	/*if (argc != 2)
	{
		printf("erreur argc");
		return 1;
	}*/

	initialise(&fdf, &mlx, &img);
	//parsing_map();
	mlx_loop(mlx.mlx_ptr);

}
