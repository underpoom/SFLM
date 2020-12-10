#pragma once
#include<SFML\Graphics.hpp>
#include "Animation.h"
#include "Collision.h "
class Player
{
public :
	Player(Texture *texture , Vector2u imageCount , float switchTime,float speed, float JumpHeight);
	~Player();

	void Update(float deltaTime);
	void Draw(RenderWindow& window);
	void OnCollistion(sf::Vector2f direction);

	void SetPosition(float  possetx, float possety);
	

	Vector2f GetPosition(){return body.getPosition();}
	Collision GetCollision() { return Collision(body); }

	bool fallen ;
	
	

	
private:
	RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	Vector2f v;
	bool canJump;
	float jumpHeight;

	
};

