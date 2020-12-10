#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
class Collision
{
public:
	Collision(RectangleShape &body);
	~Collision();

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Collision other, sf::Vector2f& direction, float push);
	bool CheckCollisionm1(Collision other, sf::Vector2f& direction);
	bool CheckCollisionm2(Collision other, sf::Vector2f& direction);
	Vector2f GetPosition() { return body.getPosition(); }
	Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
private:
	RectangleShape& body;


};

