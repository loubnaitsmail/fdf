#include "fdf.h"

void	bressan_draw(t_fdf *image, int x0, int y0, int x1, int y1)
{
	//  p0.x => x0 , p0.y = y, t_point p1)
	int		dx;
	int		dy;
	int		erreur;
	int		diff_y;

	diff_y = 1;
	if (p0.y > p1.y)
		diff_y =-1;

	dx = (p1.x - p0.x) * 2;
	dy = (p1.y - p0.x) * 2;
	erreur = (p1.x - p0.x) * diff_y;
	while (p0.x < p1.x)
	{
		//put_pixels(image, p0.x, p0.y);
		erreur -= (dy *diff_y);
		while( erreur <= 0)
		{
			p0.y += diff_y;
			erreur += dx;
			//put_pixels(image, p0.x, p0.y);
		}
		p0.x += 1;
		while (p0.y != p1.y)
		{
		//	put_pixels(image, p0.x, p0.y);
			if (p0.y < p1.y)
				p0.y++;
			else
				p0.y--;
		}
	}
}

void	put_pixels(t_img *image, int x, int y)
{
	
			image->addr_img[y * image->line_length + x * 4] = 0xff;
			image->addr_img[y * image->line_length + x * 4 + 1] = 0xff;
			image->addr_img[y * image->line_length + x * 4 + 2] = 0Xff;
			image->addr_img[y * image->line_length + x * 4 + 3] = 0;
}

#define EPAISSEUR 5
void	draw_points(t_fdf *fdf, t_img *image)
{
	int		x;
	int		y;


	printf("resulta x %lf widtj pas %f \n", fdf->x_origin, (double)700 / fdf->zoom);
	ft_bzero(image->addr_img, image->line_length * image->height);
	y = 0;
	while (y < fdf->y_max)
	{
		x = 0;
		while (x < fdf->x_max)
		{
			for (int bonus = 0; bonus < EPAISSEUR ; bonus++)
			{
				if (x == 1)
				{
					printf("new x %d\n", (x - fdf->x_origin) * fdf->zoom);
				}
			put_pixels(image, (x - fdf->x_origin) * fdf->zoom, (y - fdf->y_origin) * fdf->zoom); // x0, y0 
			put_pixels(image, (x - fdf->x_origin) * fdf->zoom + bonus, (y - fdf->y_origin) * fdf->zoom);
			put_pixels(image, (x - fdf->x_origin) * fdf->zoom, (y - fdf->y_origin) * fdf->zoom + bonus);
			put_pixels(image, (x - fdf->x_origin) * fdf->zoom + bonus, (y - fdf->y_origin) * fdf->zoom + bonus);
			}
			x++;
		}
		y++;
	}
}

void	link_points(t_fdf *fdf)
{
	int			x;
	int			y;
	int			x0;
	int			y0;
	int			x1;
	int			y1;

	y = 0;
	while (y < fdf->y_max)
	{
		x = 0;
		while (x < fdf->x_max)
		{
			x0 = (x - fdf->x_origin) * fdf->zoom;
			y0 = (y - fdf->y_origin) * fdf->zoom;
			if (x > 0)
			{
				x1 = (x - 1 -fdf->x_origin) * fdf->zoom;
				y1 = (y - fdf->y_origin) * fdf->zoom;
				//p.x = x0
				bressan_draw(fdf, x0, y0, x1, y1;// x0, y0 x1 y1
			}
			if (y > 0)
			{
				x1 = (x - fdf->x_origin) * fdf->zoom;
				y1 = (y - 1 - fdf->y_origin) * fdf->zoom;
				bressan_draw(fdf, fdf->map[y - 1][x], fdf->map[y][x]); //la mm chose
			}
			x++;
		}
		y++;
	}
}

void information(t_fdf *fdf)
{
	printf("x_max = %d\n", fdf->x_max);
	printf("y_max = %d\n", fdf->y_max);
	int x = 0;
	int y = 0;
	while(y < fdf->y_max)
	{
		 x = 0;
		while (x < fdf->x_max)
		{
			printf("%2d ", fdf->original_map[y][x]);
			x++;
		}
		y++;
		printf("\n");
	}
	printf("imqge heigh = %d\n", fdf->mlx->img_mlx->height);
	printf("imqge widht = %d\n", fdf->mlx->img_mlx->width);
	printf("imqge line_lenght = %d\n", fdf->mlx->img_mlx->line_length);
	printf("imqge endian = %d\n", fdf->mlx->img_mlx->endian);
	printf("imqge bitpixel  = %d\n", fdf->mlx->img_mlx->bits_per_pixels);

}


void	draw(t_fdf *fdf)
{
	t_mlx	*mlx;
	mlx = fdf->mlx;
	mlx_clear_window(fdf->mlx->mlx_ptr, fdf->mlx->win_ptr);
	draw_points(fdf, mlx->img_mlx);
	information(fdf);
	//link_points(fdf);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_mlx->img_ptr, 0, 0);

}
