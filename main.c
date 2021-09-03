
#include "fdf.h"

#define WIDTH 700
#define HEIGHT 700

void	initialise(t_fdf *fdf, t_mlx *mlx, t_img *img)
{
	img->width = WIDTH;
	img->height = HEIGHT;

	fdf->zoom = 21;
	
	printf("resulta x %lf widtj pas %f \n", fdf->x_origin, (double)WIDTH / fdf->zoom);
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
	if (!parsing_map(&fdf, argv[1]))
	{
		printf("Error Parsing Map");
		return(0);
	}
	fdf.x_origin = - ((img.width / fdf.zoom) - fdf.x_max) / 2;
	fdf.y_origin = - ((img.height / fdf.zoom) - fdf.y_max ) / 2;
	draw(&fdf);
	mlx_loop(mlx.mlx_ptr);
	return(0);
}
