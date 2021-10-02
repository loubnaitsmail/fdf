NAME = fdf

INC=/usr/lib
DIR_OBJ = obj
DIR_SRC = srcs

SRCS = draw_line.c main.c parsing.c projection.c draw.c draw_line_up.c

OBJ = $(addprefix obj/, $(patsubst %.c, %.o, $(SRCS)))

#mac_os
CFLAGS = -fsanitize=address -Iinclude -framework OpenGL -framework AppKit -Iminilibx_macos -Wall -Wextra libmlx.a
CFLAG2 = -fsanitize=address -Iinclude -Iminilibx_macos -Wall -Wextra 
#linux
#CFLAG2 = -fsanitize=address -Iinclude -Iminilibx-linux -Wall -Wextra -lmlx -lXext -lX11 -lm -lbsd -Lminilibx-linux -L$(INC)
#CFLAG = $(CFLAGS) libmlx.a 

all: $(NAME)

$(OBJ): $(DIR_OBJ)%.o: $(DIR_SRC)%.c
		gcc -o $@ $(CFLAG2)  -c $<

$(NAME):	$(OBJ)
			make -C minilibx_macos
			make -C libft
			mkdir -p $(DIR_OBJ)
			gcc -o $(NAME) $(OBJ) $(CFLAGS) libft/libft.a

clean:
			rm -f $(NAME) $(OBJ)

re:	clean all
