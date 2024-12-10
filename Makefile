raylib-bouncy : main.cpp
	g++ main.cpp -o raylib-bouncy -I./include -L./lib -lraylib -Wl,-rpath,./lib -static

run : raylib-bouncy
	./raylib-bouncy