d:	../main.cpp
	cd .. ; g++ main.cpp src/*.cpp src/*.c classes/*.cpp `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes -Iclasses; ./a.out ; cd classes

a asan:	main.cpp
	cd .. ; g++ main.cpp src/*.cpp src/*.c classes/*.cpp -g -fsanitize=address `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes -Iclasses; ./a.out ; cd classes

r run:
	cd .. ; ./a.out ; cd classes

git:
	git add -A ; git commit -m "sync" ; git push

p:
	git pull
