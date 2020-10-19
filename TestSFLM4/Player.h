#pragma once
#include<SFML\Graphics.hpp>
#include "Animation.h"
#include "Collision.h "
class Player
{
public :
	Player(Texture *texture , Vector2u imageCount , float switchTime,float speed);
	~Player();

	void Update(float deltaTime);
	void Draw(RenderWindow& window);

	Vector2f GetPosition(){return body.getPosition();}
	Collision GetCollision() { return Collision(body); }
		
		

	
private:
	RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

};

