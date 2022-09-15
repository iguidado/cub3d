# NAME

NAME = cub3d
N_LIB = libft.a
N_MLX = libmlx_Linux.a
N_GNL = libgnl.a

N_TEST = test
N_MAIN_TEST = unit_test.c


N_SRC = main.c\
		ft_export_bmp.c\
		ft_preset_struct.c\
		ft_parse_cub.c\
		ft_parse_utils.c\
		ft_get_num_value.c\
		ft_get_texture.c\
		ft_add_map.c\
		ft_add_map_utils.c\
		ft_map_analysis.c\
		ft_load_game.c\
		ft_inputs.c\
		ft_render_screen.c\
		ft_manage_block.c\
		ft_manage_error.c\
		ft_unit_test.c\
		ft_wipe.c

#	ft_unit_test.c\

N_OBJ = $(N_SRC:.c=.o)

N_HDR = cub3d.h\
	parse_cub.h

N_HDR_MLX = mlx.h
N_HDR_LIB = libft.h
N_HDR_GNL = get_next_line.h

# Directory
D_INC = include
D_SRC = src

D_LIB = libft
D_MLX = mlx
D_GNL = gnl

# Path = Directory + name
P_LIB = $(D_LIB)/$(N_LIB)
P_MLX = $(D_MLX)/$(N_MLX)
P_GNL = $(D_GNL)/$(N_GNL)
P_SRC = $(addprefix $(D_SRC)/, $(N_SRC))
P_OBJ = $(P_SRC:.c=.o)
P_INC = $(addprefix $(D_INC)/, $(N_HDR))\
		$(D_LIB)/include/$(N_HDR_LIB)\
		$(D_MLX)/$(N_HDR_MLX)\
		$(D_GNL)/$(N_HDR_GNL)

# Compiler
CC = clang
WFLAG = -Wall -Werror -Wall
DFLAG = -g3 -fsanitize=address
INC_OBJ = -I$(D_INC) -I$(D_MLX) -I$(D_LIB)/include -I$(D_GNL)
INC_FLAG = $(INC_OBJ) -lXext -lX11 -lbsd -lm
FLAGS = $(WFLAG)
FLAGS += $(DFLAG)

all : $(NAME)

$(NAME) : $(P_OBJ) $(N_LIB) $(N_MLX) $(N_GNL)
	$(CC) -o $(NAME) $(FLAGS) $(P_OBJ) $(INC_FLAG) $(P_LIB) $(P_MLX) $(P_GNL)

%.o : %.c $(P_INC)
	$(CC) $(FLAGS) $(INC_OBJ) -o $@ -c $<

$(N_LIB) : $(D_LIB)
	make -C $(D_LIB)

$(N_MLX) : $(D_MLX)
	make -C $(D_MLX)

$(N_GNL) : $(D_GNL)
	make -C $(D_GNL)

clean :
	make clean -C $(D_LIB)
	make clean -C $(D_MLX)
	make clean -C $(D_GNL)
	rm -rf $(P_OBJ)

fclean : clean
	make fclean -C $(D_LIB)
	make fclean -C $(D_GNL)
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
