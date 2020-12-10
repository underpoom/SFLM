#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"Collision.h"
using namespace sf;
class monster1
{
public:
	monster1(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,Vector2f pos);
	~monster1();
	void Updatem1(float deltatimem1, float posx, float posy);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return bodym1.getPosition(); }
	Collision GetCollider() { return Collision(bodym1); }

private:
	sf::RectangleShape bodym1;
	Animation animation;
	unsigned int rowm1;
	float speedm1;
	bool faceRightm1;
	int chk = 0;

};