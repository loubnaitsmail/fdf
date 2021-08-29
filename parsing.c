#include "fdf.h"

#define		BUFFER_MAP 128




t_fdf	*parsing_map(t_fdf *fdf, const char file)
{
	int		fd;
	char	*line;
	int		gnt_ret;

	fd = open(file, O_RDONLY);
	gnt_ret = get_next_

}
