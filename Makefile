CC     = cc
RM     = rm -rf

NAME   = fdf
OBJDIR = objs
MLX_LIB = mlx/libmlx.a

# MLX (MiniLibX) configuration
INC    = /usr/include
INCLIB = $(INC)/../lib
CFLAGS = -I$(INC) -Imlx -O3 -g
LFLAGS = -Lmlx -lmlx -L$(INCLIB) -lXext -lX11 -lm

SRC = srcs/main.c
OBJS   = $(SRC:srcs/%.c=$(OBJDIR)/%.o)

# Main targets
all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS)

$(MLX_LIB):
	$(MAKE) -C mlx

$(OBJDIR)/%.o: srcs/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(MAKE) -C mlx clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
