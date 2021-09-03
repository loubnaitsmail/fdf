#include "fdf.h"
#include <fcntl.h>
#include "libft/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>

#define		BUFFER_MAP 128

int		count_nbr_str(char *line)
{
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (line[++i])
	{
		if(line[i] >= '0' && line[i] <= '9')
		{
			size++;
			while (line[i] >= '0' && line[i] <= '9')
				i++;
		}
	}
	return (size);
}

int *fill_tab(char *line)
{
	int			*tab;
	int			i;
	int			j;
	int			size_tab;

	i = 0;
	j = 0;
	size_tab = count_nbr_str(line) + 1;
	tab = (int *)ft_memalloc(sizeof(int) * (size_tab + 1));
	while (line[i] && j < size_tab + 1)
	{
		tab[j] = ft_atoi(&line[i]);
		while (line[i] && !ft_isdigit(line[i]))
			i++;
		while (line[i] && ft_isdigit(line[i]))
			i++;
		j++;
	}

	int x;
	for(x = 0; x < size_tab; x++)
		printf("%2d ", tab[x]);
	printf("\n");

	return (tab);
}

t_fdf	*parsing_map(t_fdf *fdf, const char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	fdf->y_max = 0;
	if (fd < 0 || read(fd, NULL, 0) == -1)
		return (NULL);
	while (get_next_line(fd, &line) > 0 && fdf->y_max < BUFFER_MAP)
	{
		if (fdf->y_max == 0)
			fdf->original_map = (int **) ft_memalloc(sizeof(int *) * (BUFFER_MAP + 1));
		//printf("%s\n", line);
		fdf->original_map[fdf->y_max] = fill_tab(line);
		fdf->y_max++;
		free(line);
	}
	if (line)
		free(line);
	// sorti boucle soit erreur (gnl < 0) ou teminer (gnl == 0)
	return (fdf);
}

/*
int main(int argc, const char *argv[])
{
	t_fdf fdf;
	if (argc != 2)
	{
		printf("erreur argc\n");
		return 1;
	}


	parsing_map(&fdf, argv[1]);
	// fre fdf.map
	return 0;
}*/
