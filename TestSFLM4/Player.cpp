#include "Player.h"

Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed, float jumpHeight):
animation(texture , imageCount , switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	body.setSize(Vector2f(100.0*0.55f, 150.0*0.55f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(0.0f, 699-300.0f);
	body.setTexture(texture);

}
Player::~Player()
{
}
void Player::Update(float deltaTime)
{
	v.x = 0.0f;
	
		
	if (fallen == 0)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::A))
			v.x -= speed;
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
			v.x += speed;
		if (Keyboard::isKeyPressed(Keyboard::Key::S))
			v.y += speed;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
			canJump = false;

			v.y = -sqrtf(2.0f * 981.0f * jumpHeight);
		}

		v.y += 981.0f * deltaTime;
		canJump = false;








		if (v.x == 0.0f)
		{
			row = 0;
		}
		else {
			row = 1;
			if (v.x > 0.0f)
				faceRight = true;
			else faceRight = false;
		}

		animation.Update(row, deltaTime, faceRight);
		body.setTextureRect(animation.uvRect);
		body.move(v * deltaTime);
	}
}
void Player::Draw(RenderWindow& window)
{
	window.draw(body);

}
void Player::OnCollistion(sf::Vector2f direction)
{
	if (direction.x < 0.0f) {
		v.x = 0.0f;
	}
	else if (direction.x > 0.0f) {
		v.x = 0.0f;
	}
	if (direction.y < 0.0f) {
		v.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f) {
		v.y = 0.0f;
	}
}
