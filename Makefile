NAME = main

SOURCES = main.c

OBJECTS = $(subst .c,.o,$(SOURCES))

FLAGS = -Wall -Wextra #-Werror
LINKS = -I /usr/local/include -L /usr/local/lib \
		-l mlx  -framework OpenGL -framework Appkit

# Remember to implement your rules...
all : $(NAME)
$(NAME): $(OBJECTS)
	cc $(SOURCES) -o $(NAME) $(FLAGS) $(LINKS)

