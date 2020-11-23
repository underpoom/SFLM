#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;
class background
{
public:
	background(Vector2f size,String file,Vector2f pos);
	~background();
	void ddraw(RenderWindow& window);


private:
	RectangleShape body;
	Vector2f size;
	String file;
	Vector2f pos;
};

