d:	main.cpp
	g++ main.cpp src/*.cpp src/*.c `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes; ./a.out

a asan:	main.cpp
	g++ main.cpp src/*.cpp src/*.c -g -fsanitize=address `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes; ./a.out

r run:
	./a.out

git:
	git add -A ; git commit -m "sync" ; git push

p:
	git pull
