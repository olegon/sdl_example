OBJS = *.cpp

CC = g++	

COMPILER_FLAGS = -W -Wall -O3

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = sdl-example.out

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
