g:
	git add -A ; git commit -m "sync" ; git push
d:	main.cpp
	g++ main.cpp src/*.cpp src/*.c classes/*.cpp `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes -Iclasses -Isounds; ./a.out

t:	main.cpp
	g++ main.cpp src/*.cpp src/*.c classes/*.cpp `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes -Iclasses -Isounds

a asan:	main.cpp
	g++ main.cpp src/*.cpp src/*.c -g -fsanitize=address classes/*.cpp `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes -Iclasses -Isounds

r run:
	./a.out

c clean:
	rm ./a.out

git:
	git add -A ; git commit -m "sync" ; git push

p:
	git pull

g grant:
	cd ~/galaxian_clone/ ; make r ; cd ~/mygalaxian/ ; clear
