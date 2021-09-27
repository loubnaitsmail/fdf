NAME = fdf

#INC=/usr/lib
#INCLUDE= -I. -Iminilibx-linux
INCLUDE= -I./include
DIR_OBJ = obj

SRCS = draw_line.c main.c parsing.c projection.c

OBJ = $(addprefix srcs/, $(patsubst %.c, %.o, $(SRCS)))

CFLAGS = -fsanitize=address -Iinclude -framework OpenGL -framework AppKit -Iminilibx_macos libmlx.a

#CFLAGS = -Wall -lmlx -lXext -lX11 -lm -lbsd  -Lminilibx-linux -L$(INC) $(INCLUDE)

all: $(NAME)

$(NAME):	$(OBJ)
			make -C minilibx_macos
			mkdir -p $(DIR_OBJ)
			gcc -o $(NAME) $(OBJ) $(CFLAGS) libft.a
			mv $(OBJ) $(DIR_OBJ)

clean:
			rm -f $(NAME) $(OBJ) $(DIR_OBJ)/*

re:	clean all