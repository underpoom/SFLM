#pragma once
#include <SFML\Graphics.hpp>
#include "Collision.h"
using namespace sf;
class Platform
{
public:
	Platform(Texture* texture, Vector2f size, Vector2f position,Color color);
	~Platform();
	void Draw(RenderWindow& window);
	Collision GetCollision() { return Collision(body); }
private :
	RectangleShape body;
};

