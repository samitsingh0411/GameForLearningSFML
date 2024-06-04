#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

//Falling Object

class FallingObject {
public:
	sf::RectangleShape FallingRect;

	FallingObject();
	void DecendObject();
};


// Create Window


class CreateWindow {

public:
	sf::RenderWindow* GameWindow;
	sf::Event GameEvent;
	int score;
	std::vector<FallingObject> FallingObjectList;
	int FrameRate;
	sf::Color ScreenColor = sf::Color::Cyan;
	sf::Vector2i MousePosition;

	//Constructors Distructors
	CreateWindow();
	~CreateWindow();

	//Main Methods
	void Update();
	void Clear();
	void Display();

	//Functionality Functions
	void PollEvent();
	void SwapnNewCubes();

private:
	void CheckFallingObject();
	void RemoveElement(int i);
};


