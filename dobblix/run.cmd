g++ -c main.cpp -c display.cpp -c code.cpp -IC:\SFML\include
g++ -o dobblx main.o display.o code.o -LC:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lwinmm -lgdi32 -lfreetype -lsfml-audio -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg
start dobblx.exe    