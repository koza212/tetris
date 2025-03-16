#include "raylib.h"
#include "raymath.h"
#include "game.h"   
#include "lib.h"	

int main(){
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);  // Set before InitWindow
	//InitWindow(0, 0, "Fullscreen Window"); // Width and height ignored in fullscreen
	InitWindow(500, 620, "tetris");
	SetTargetFPS(60);

	Game game = Game();
	
	while (!WindowShouldClose()) {
		game.Run();
	}

	CloseWindow();

}