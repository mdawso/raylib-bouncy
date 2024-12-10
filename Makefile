raylib-bouncy : main.cpp
	g++ main.cpp -o raylib-bouncy -I./include -L./lib -lraylib -Wl,-rpath,./lib

run : raylib-bouncy
	./raylib-bouncy