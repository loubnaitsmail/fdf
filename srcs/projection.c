#include "fdf.h"

void	iso(t_point *p)
{
    double	previous_x;
    double	previous_y;

    previous_x = p->x;
    previous_y = p->y;
    p->x = (previous_x - previous_y) * cos(0.523599);
    p->y = - p->z + (previous_x + previous_y) * sin(0.523599);
}

void	change_to_iso(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->y_max)
	{
		j = 0;
		while (j < fdf->x_max)
		{	
			iso(&(fdf->map[i][j]));
			j++;
		}
		i++;
	}
}

 int	change_projection(t_fdf *fdf)
{
	if (fdf->projection == ISOMETRIC)
	{
		fdf->projection = PARALLELE;
		for (int i = 0; i <  fdf->y_max ; i++)
		{
			for (int j = 0; j < fdf->x_max ; j++)
			{
				fdf->map[i][j].y = i;
				fdf->map[i][j].x = j;
				fdf->map[i][j].z = fdf->original_map[i][j];
			}
		}
	}
	else if (fdf->projection == PARALLELE)
	{
		fdf->projection = ISOMETRIC;
		change_to_iso(fdf);
	}
	/*else
	{
		fdf->projection = PARALLELE;
	}*/
	return (1);
}

/*int	keys_action(int key, void *param)
{

	t_fdf	*fdf;
	t_mlx	*mlx;

	fdf = (t_fdf *)param;
	mlx = fdf->mlx;
	printf("key %d\n",key);
	if (key == CHANGE_PROJECTION)
		change_projection(fdf);
	return (1);
}*/
