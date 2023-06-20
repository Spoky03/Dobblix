g++ -c main.cpp -c display.cpp -c code.cpp -DSFML_STATIC -IC:\SFML\include
g++ -o dobblx main.o display.o code.o -static -LC:/SFML/lib -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg
start dobblx.exe