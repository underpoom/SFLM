#include "monster1.h"
int monster1hp = 2;
bool i = false;
using namespace sf;
monster1::monster1(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,Vector2f pos) :
	animation(texture, imageCount, switchTime)
{
	this->speedm1 = speed;
	rowm1 = 0;
	faceRightm1 = true;
	

	bodym1.setSize(sf::Vector2f(263.0f/5, 308.0f/5));
	bodym1.setPosition(pos.x, pos.y);

	bodym1.setTexture(texture);
}

monster1::~monster1() {}
void monster1::Updatem1(float deltatimem1,float posx,float posy) {
	float x = bodym1.getPosition().x;
	float y = bodym1.getPosition().y;
	sf::Vector2f movement(0.0f, 0.0f);
	if (chk == 0) {
		movement.x -= speedm1 * deltatimem1;
		if (x <= posx) {
			chk = 1;
		}
	}
	if (chk == 1) {
		movement.x += speedm1 * deltatimem1;
		if (x >= posy) {
			chk = 0;
		}
	}
	if (chk == 2) {
		bodym1.setPosition(sf::Vector2f(0.0f, 1000.0f));
	}

	rowm1 = 0;
	if (chk == 0) {
		faceRightm1 = true;
	}
	else {
		faceRightm1 = false;
	}

	animation.Update(rowm1, deltatimem1, faceRightm1);
	bodym1.setTextureRect(animation.uvRect);
	bodym1.move(movement);
}

void monster1::Draw(sf::RenderWindow& window)
{
	window.draw(bodym1);
}