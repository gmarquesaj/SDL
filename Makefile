gsdl.o: SDL.cpp
	clang++ -c SDL.cpp -o gsdl.o
exemplo: gsdl.o
	clang++  -lSDL2 -lSDL2_ttf teste.cpp -o teste && mangohud --dlsym ./teste
clear:
	rm -f *.o