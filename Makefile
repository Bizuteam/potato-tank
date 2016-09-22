CC = g++$
CFLAGS = -Wall -pedantic -std=c++11

ifdef SYSTEMROOT
	# Si Windows
	LDFLAGS = -lm -lallegro-5.0.10-md -lallegro_image-5.0.10-md
else
	ifeq ($(shell uname), Linux)
	# Si Linux
		LDFLAGS = -lm `pkg-config --libs allegro-5.0 allegro_main-5.0 allegro_image-5.0`
	endif
endif

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
