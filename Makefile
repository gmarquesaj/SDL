app =  app.elf
comp = clang++
all: teste.o SDL.o
	clear
	$(comp) teste.o SDL.o -o $(app) -O3 -lSDL2 -lSDL2_ttf
	./$(app)
SDL.o: SDL.cpp
	$(comp) -c SDL.cpp  -O3

teste.o: teste.cpp
	$(comp) -c teste.cpp  -O3

clear:
	rm -f *.o *.out app img/*
	clear
