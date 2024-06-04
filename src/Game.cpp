#include "Game.h"

// Game Class Methdos

CreateWindow::CreateWindow() {
	GameWindow = new sf::RenderWindow(sf::VideoMode(800, 800), "Click the Falling Blocks", sf::Style::Titlebar | sf::Style::Close);
	score = 0;
	FallingObjectList.reserve(15);
	GameWindow->setFramerateLimit(24);
	for (int i = 0; i < 10; i++) {
		FallingObject TempRect;
		FallingObjectList.push_back(TempRect);
	}
}

CreateWindow::~CreateWindow() {
	delete GameWindow;
}

void CreateWindow::Clear() {
	GameWindow->clear(ScreenColor);
}
void CreateWindow::Display() {
	for (int i = 0; i < FallingObjectList.size(); i++) {
		GameWindow->draw((FallingObjectList[i].FallingRect));
	}
	GameWindow->display();
}

void CreateWindow::PollEvent() {
	while (GameWindow->pollEvent(GameEvent)) {
		switch (GameEvent.type) {
		case sf::Event::Closed:
			GameWindow->close();
			break;
		case sf::Event::KeyPressed:
			if (GameEvent.key.code == sf::Keyboard::Escape)
				GameWindow->close();
			break;
		case sf::Event::MouseButtonReleased:

			MousePosition = sf::Mouse::getPosition(*GameWindow);
			std::cout << MousePosition.x << " " << MousePosition.y << std::endl;

			for (int i = 0; i < FallingObjectList.size(); i++) {
				auto &CurrentElement = FallingObjectList[i];
				sf::FloatRect GlobalBounds = CurrentElement.FallingRect.getGlobalBounds();
				if (GlobalBounds.contains((sf::Vector2f)MousePosition)) {
					RemoveElement(i);
				}
			}
			break;

		default:
			break;
		}
	}

}

void CreateWindow::SwapnNewCubes() {
	int RandomArrSize = rand() % 15;
	if (FallingObjectList.size() < RandomArrSize) {
		FallingObject TempFallingRect;
		FallingObjectList.push_back(TempFallingRect);
	}
}

void CreateWindow::CheckFallingObject() {
	for (int i = 0; i < FallingObjectList.size(); i++) {
		if ((FallingObjectList[i].FallingRect.getPosition()).y >= 800) {
			FallingObjectList.clear();
			std::cout << "You Lost!" << std::endl;
			ScreenColor = sf::Color::Red;
		}
	}
}

void CreateWindow::RemoveElement(int i) {
	FallingObject TempObj;
	FallingObjectList.erase(FallingObjectList.begin() + i);
	FallingObjectList.push_back(TempObj);
	FallingObjectList.pop_back();
}

void CreateWindow::Update() {
	CheckFallingObject();
	SwapnNewCubes();
	PollEvent();
	for (int i = 0; i < FallingObjectList.size(); i++) {
		FallingObjectList[i].DecendObject();
	}

}




// Falling Object Class Methods

FallingObject::FallingObject() {
	float RandomSize = (rand() % 50) + 20;
	int RandomColor = rand() % 6;
	float RandomLocationX = rand() % 740;
	float RandomLocationY = rand() % 20;
	
	//Setting the Random size

	FallingRect.setSize(sf::Vector2f(RandomSize, RandomSize));

	//Setting the random color
	switch (RandomColor) {

	case 0:
		FallingRect.setFillColor(sf::Color::Blue);
		break;
	case 1:
		FallingRect.setFillColor(sf::Color::Green);
		break;
	case 2:
		FallingRect.setFillColor(sf::Color::Yellow);
		break;
	case 3:
		FallingRect.setFillColor(sf::Color::Magenta);
		break;
	case 4:
		FallingRect.setFillColor(sf::Color::Black);
		break;
	case 5:
		FallingRect.setFillColor(sf::Color::Red);
		break;
	}

	//Setting Initial Location

	FallingRect.setPosition(sf::Vector2f(RandomLocationX, RandomLocationY));
}

void FallingObject::DecendObject() {
	sf::Vector2f CurrentObjPos = FallingRect.getPosition();
	FallingRect.setPosition(sf::Vector2f(CurrentObjPos.x, CurrentObjPos.y + 2));
}

