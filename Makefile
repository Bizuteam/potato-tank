#OBJS specifies which files to compile as part of the project
OBJS_SDL = main_sdl.c
OBJS_AL = main_al.c

#OBJ_NAME specifies the name of our exectuable
OBJ_SDL_NAME = sdl.out
OBJ_AL_NAME = al.out

#This is the target that compiles our executable
sdl : $(OBJS_SDL)
	g++ -Wall $(OBJS_SDL) -lSDL2 -o $(OBJ_SDL_NAME)

al: $(OBJS_AL)
	gcc -Wall $(OBJS_AL) -o $(OBJ_AL_NAME) `pkg-config --libs allegro-5.0 allegro_main-5.0 allegro_image-5.0` -lm

clean:
	-@rm *.out 2>/dev/null || true
	@echo "rm *.out"
