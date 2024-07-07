exemplo: libgsdl.a
	clang++ -lSDL2 -lSDL2_ttf teste.cpp -L. -lgsdl -o teste && mangohud --dlsym ./teste

SDL.o: SDL.cpp
	clang++ -c SDL.cpp
imagem.o: imagem.cpp
	clang++ -c imagem.cpp
botao.o:botao.cpp
	clang++ -c botao.cpp
rotulo.o:rotulo.cpp
	clang++ -c rotulo.cpp
libgsdl.a: SDL.o imagem.o botao.o rotulo.o
	ar rcs ./libgsdl.a  SDL.o imagem.o botao.o rotulo.o
clear:
	rm -f *.o *.a