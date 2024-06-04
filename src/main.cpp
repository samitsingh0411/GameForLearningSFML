#include "Game.h"

int main() {
	CreateWindow Game;
	while (Game.GameWindow->isOpen()) {
		Game.Clear();
		Game.Update();
		Game.Display();
	}
}