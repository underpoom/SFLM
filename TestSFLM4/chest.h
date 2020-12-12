#pragma once
#include <SFML\Graphics.hpp>
#include "Collision.h"
using namespace sf;
class chest
{
public:
	chest(Texture* texture, Vector2f size, Vector2f position);
	~chest();
	void Draw(RenderWindow& window);
	Collision GetCollision() { return Collision(body); }
	Collision GetCollider() { return Collision(body); }
private:
	RectangleShape body;
};


