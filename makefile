d:	main.cpp
	g++ main.cpp src/*.cpp src/*.c `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes; ./a.out

t:
	g++ *.cpp *.c `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes

exe:	main.cpp
	g++ *.cpp src/*.cpp src/*.c `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes 

a asan:
	g++ *.cpp *.c -g -fsanitize=address `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes 

r run:
	./a.out

clean:
	rm a.out

c:
	rm a.out

git:
	git add -A ; git commit -m "sync" ; git push

p:
	git pull
