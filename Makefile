NAME = fdf

#INC=/usr/lib
#INCLUDE= -I. -Iminilibx-linux
INCLUDE= -I./include
DIR_OBJ = obj
DIR_SRC = srcs

SRCS = draw_line.c main.c parsing.c projection.c

OBJ = $(addprefix obj/, $(patsubst %.c, %.o, $(SRCS)))

CFLAGS = -fsanitize=address -Iinclude -framework OpenGL -framework AppKit -Iminilibx_macos -Wall -Wextra libmlx.a
CFLAG2 = -fsanitize=address -Iinclude -Iminilibx_macos -Wall -Wextra 

all: $(NAME)

$(OBJ): $(DIR_OBJ)%.o: $(DIR_SRC)%.c
		gcc -o $@ $(CFLAG2)  -c $<
#CFLAGS = -Wall -lmlx -lXext -lX11 -lm -lbsd  -Lminilibx-linux -L$(INC) $(INCLUDE)


$(NAME):	$(OBJ)
			make -C minilibx_macos
			mkdir -p $(DIR_OBJ)
			gcc -o $(NAME) $(OBJ) $(CFLAGS) libft.a

clean:
			rm -f $(NAME) $(OBJ)

re:	clean all
