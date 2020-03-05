HEAD_PATH	=					.
HEAD_NAME	=					includes/cube.h minilibx_opengl_20191021/mlx.h
HEADER		=					$(addprefix $(HEAD_PATH)/,$(HEAD_NAME))
MINILIBX	=					libmlx.a
MINILIBXS	=					minilibx_opengl_20191021/libmlx.a
LIB			=					libft.a
LIBS		=					libft/libft.a
SRC_PATH	=					srcs
SRCS_NAME	=		ft_sprite_raycasting.c raycasting.c main.c \
					ft_parsing.c ft_parsing_two.c ft_parsing_three.c \
					ft_puterror.c
OBJS		= 					${SRCS:.c=.o}
NAME		= 					Cub3D
RM			= 					rm -f
FLAGS 		= 					#-Wall -Wextra -Werror -g3
GFLAGS 		=					-lmlx -framework OpenGL -framework AppKit
SRCS 		= 					$(addprefix $(SRC_PATH)/,$(SRCS_NAME))

all:							$(MINILIBX) $(LIB) CUBE $(NAME)
%.o: %.c 						$(HEADER) $(LIBS) $(MINILIBXS)
								@echo "\033[0;32m[OK] \033[0m \033[0;33m Compiling:\033[0m" $<
								@gcc $(FLAGS) -c $< -o $@
$(NAME):						$(OBJS) $(HEADER)
								@gcc $(FLAGS) $(OBJS) -L minilibx_opengl_20191021 $(GFLAGS) $(LIBS) -o $(NAME) -lm
								@echo "\x1b[36m\n[OK] \033[0m \x1b[35m Compiling Cube3D\033[0m"
$(MINILIBX) :
								@$(MAKE) -C minilibx_opengl_20191021 all
$(LIB):
								@$(MAKE) -C libft all
clean:
								@$(MAKE) -C libft clean
								@$(MAKE) -C minilibx_opengl_20191021 clean
								@echo "\x1b[36m[OK] \033[0m \x1b[34m Removing ALL File object\033[0m"
								@$(RM) $(OBJS)
fclean:							clean
								@$(MAKE) -C libft fclean
								@echo "\x1b[36m[OK] \033[0m \x1b[32m All is Removing\033[0m"
								@$(RM) $(NAME)
re:								fclean all
CUBE:
								@echo ---------------------------------------------
								@echo "	 __,,  ,__, __,  __   _ , "
								@echo "	|   |  ||_)|__   __| |  \ "
								@echo "	|__ |__||_)|__   __| |_ / "
								@echo "	~~   ~~ ~  ~~    ~~  ~~   "
								@echo ""
.PHONY: 						clean fclean
