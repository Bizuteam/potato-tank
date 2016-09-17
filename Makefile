CC = g++$
CFLAGS = -Wall -pedantic -std=c++11
LDFLAGS = -lm `pkg-config --libs allegro-5.0 allegro_main-5.0 allegro_image-5.0`

#OBJS specifies which files to compile as part of the project
OBJS_AL = main.cpp Bullet.cpp Player.cpp Map.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_AL_NAME = potato-tank.out

#This is the target that compiles our executable
all: $(OBJS_AL)
	$(CC) $(OBJS_AL) -o $(OBJ_AL_NAME) $(LDFLAGS) $(CFLAGS)

clean:
	-@rm *.out 2>/dev/null || true
	@echo "rm *.out"
