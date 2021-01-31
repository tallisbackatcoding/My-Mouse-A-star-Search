SOURCES = main.c functions.c bit_field.c stack.c algo.c dict.c set.c queue.c bstset.c
HEADERS = functions.h bit_field.h stack.h algo.h dict.h set.h queue.h bstset.h
SRCS_PATH = src/
INCLUDES_PATH = headers/
SRCS = $(addprefix $(SRCS_PATH), $(SOURCES))
INCLUDES = $(addprefix $(INCLUDES_PATH), $(HEADERS))
OBJECTS = $(SOURCES:.c=.o)
CC = gcc -lm -std=c17 -O3 -g3 -fsanitize=address 
CFLAGS = -Wall
NAME = mouse

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS)

$(OBJECTS): $(SRCS) $(INCLUDES)
	$(CC) -c $(CFLAGS) $(SRCS) -I$(INCLUDES_PATH)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
