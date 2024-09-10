NAME= fractol
BNS_NAME= fractol_bonus

CC= cc
CFILES = fractol.c render.c ft_strcmp.c ft_isdigit.c ft_strlen.c ft_utils.c ft_fractol_error.c ft_hooks.c ft_putstr.c
BNSCFILES = fractol.c render_bonus.c ft_strcmp.c ft_isdigit.c ft_strlen.c ft_utils.c ft_fractol_error_bonus.c ft_hooks_bonus.c ft_putstr.c

OFILES= $(CFILES:.c=.o)
BNSOFILES= $(BNSCFILES:.c=.o)

CFLAGS= -Wall -Wextra  -Werror
LINKS= -I /usr/local/include -L /usr/local/lib \
		-l mlx  -framework OpenGL -framework Appkit

all: $(NAME)
$(NAME): $(OFILES)
	cc $(CFILES) -o $(NAME) $(CFLAGS) $(LINKS)
bonus: $(BNSOFILES)
	cc $(BNSCFILES) -o $(NAME) $(CFLAGS) $(LINKS)
clean:
	rm -rf $(OFILES) $(BNSOFILES)
fclean: clean
	rm -rf $(NAME)
re: fclean all
.PHONY: all bonus clean fclean re

