#ifndef _FDF_H
#define _FDF_H

#include "../include/mlx.h"
#include <fcntl.h>
#include "../libft/get_next_line.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#define WIDTH 700
#define HEIGHT 700
#define BUFFER_MAP 1024
#define EPAISSEUR 1
#define QUIT 12
#define ESC 53
#define RIGHT 124
#define UP 126
#define DOWN 125
#define LEFT 123

#define CHANGE_PROJECTION 35
#define DEBUG 0


typedef struct	s_img
{
	void*			img_ptr;
	unsigned int*	addr_img;
	int				height;
	int				width;
	int				bits_per_pixels;
	int				line_length;
	int				endian;
}					t_img;

typedef struct		s_mlx
{
	void*			mlx_ptr;
	void*			win_ptr;
	t_img*			img_mlx;
}					t_mlx;

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
}				t_point;

typedef enum		e_projection
{
					ISOMETRIC,
					PARALLELE
}					t_projection;

typedef struct		s_fdf
{
	int				**original_map;
	t_point			**map;
	t_mlx			*mlx;
	int				x_max;
	int				y_max;
	double			x_origin;
	double			y_origin;
	int				zoom;
	t_projection	projection;
}					t_fdf;

	int		count_nbr_str(char *line);
	int		*fill_tab(char *line, t_fdf *fdf);
	t_fdf	*parsing_map(t_fdf *fdf, const char *file);
	void	draw(t_fdf *fdf);
	 int	change_projection(t_fdf *fdf);

#endif
