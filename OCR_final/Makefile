#Makefile

CC=gcc

CFLAGS= `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl` -MMD
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image` `pkg-config --libs gtk+-3.0` -rdynamic


user_interface: Preprocessing/pixel_operations.o Preprocessing/grayscale.o Preprocessing/display.o Segmentation/hough.o Segmentation/segment.o Preprocessing/drawsudoku.o UI/user_interface.o
	$(CC) -g -o UI/user_interface Preprocessing/pixel_operations.o Preprocessing/grayscale.o Preprocessing/display.o Segmentation/hough.o Segmentation/segment.o Preprocessing/drawsudoku.o UI/user_interface.o -lm $(LDLIBS)



clean:
	rm *.o -f

#END
