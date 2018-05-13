CXX = gcc
LDFLAGS = `sdl2-config --cflags --libs`
LDJFLAGS = `pkg-config --cflags --libs jansson`
OBJS = main.o rasterizer.o matrix.o vector3.o mesh.o camera.o display.o input.o bsp.o utils.o
OBJS2 = main.c rasterizer.c matrix.c vector3.c mesh.c camera.c display.c input.c bsp.c utils.c

all:
	$(CXX) -o pixelator -lm $(LDFLAGS) $(LDJFLAGS) $(OBJS2)

clean:
	rm -f pixelator
	rm -f $(OBJS)

main.o: main.c
rasterizer.o: rasterizer.c
vector3.o: vector3.c
matrix.o: matrix.c
mesh.o: mesh.c
camera.o: camera.c
display.o: display.c
input.o: input.c
bsp.o: bsp.c
utils.o: utils.c