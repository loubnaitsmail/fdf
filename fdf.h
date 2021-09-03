#ifndef _FDF_H
#define _FDF_H

#include <mlx.h>
#include <fcntl.h>
#include "libft/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <string.h>

typedef struct	s_img
{
	void*		img_ptr;
	char*		addr_img;
	int			height;
	int			width;
	int			bits_per_pixels;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void*		mlx_ptr;
	void*		win_ptr;
	t_img*		img_mlx;
}				t_mlx;

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
}				t_point;

typedef struct	s_fdf
{
	int			**original_map;
	t_point		**map;
	t_mlx		*mlx;
	int			x_max;
	int			y_max;
}				t_fdf;


	int		count_nbr_str(char *line);
	int *fill_tab(char *line);
	t_fdf	*parsing_map(t_fdf *fdf, const char *file);



#endif
